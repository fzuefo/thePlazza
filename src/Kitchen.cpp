/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "IReception.hpp"
#include <mutex>
#include <thread>
#include <iostream>
#include "Logger.hpp"

namespace Plazza {

    using pizza_v = std::vector<Pizza>;

    Kitchen::Kitchen(unsigned long maxCooks, unsigned long reloadTime, double mul):
    _maxCooks(maxCooks),
    _reloadTime(reloadTime),
    _cookManager(std::make_unique<Cook_manager>(maxCooks, reloadTime, mul)),
    _queueTime(0)
    {
        _cookMul = mul;
        this->setIpc(std::make_shared<PlazzaIpc>());
        this->_ipc->open();
        this->_kitchenClock = std::chrono::high_resolution_clock::now();
        _status.idleTime = 0;
        _status.activeCooks = 0;
        _status.waitingOrders = 0;
        _status.timeWaitingOrder = 0;
    }

    Kitchen::~Kitchen()
    {
        this->_ipc->close();
    }

    void Kitchen::start()
    {
        return AProcess::start();
    }

    void Kitchen::_sendPizzasToCook()
    {
        while (this->_pizzaQueue.size()) {
            auto &pizza = this->_pizzaQueue.front();
            if (this->_cookManager->manag_pizza(pizza)) {
                this->_pizzaQueue.pop();
            }
            else
                return;
        }

    }

    void Kitchen::_updateStatus()
    {
        static high_res_clock idleStart;

        this->_status.activeCooks = this->_cookManager->getNbActiveCooks();
        this->_status.waitingOrders = this->_pizzaQueue.size();
        this->_status.timeWaitingOrder = this->_queueTime;
        if (this->_status.waitingOrders || this->_status.activeCooks)
            this->_status.idleTime = 0;
        else {
            if (this->_status.idleTime == 0)
                idleStart = std::chrono::high_resolution_clock::now();
            this->_status.idleTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - idleStart).count();
        }
    }


    void Kitchen::_sendStatus()
    {
        byte_v bytes;
        byte_v activeCooksBytes = this->_numToBytes(this->_status.activeCooks);
        byte_v waitingOrdersBytes = this->_numToBytes(this->_status.waitingOrders);
        byte_v timeWaitingOrderBytes = this->_numToBytes(this->_status.timeWaitingOrder);
        byte_v idleTimeBytes = this->_numToBytes(this->_status.idleTime);

        bytes.push_back(static_cast<char>(STATUS));

        bytes.insert(bytes.end(), activeCooksBytes.begin(), activeCooksBytes.end());
        bytes.insert(bytes.end(), waitingOrdersBytes.begin(), waitingOrdersBytes.end());
        bytes.insert(bytes.end(), timeWaitingOrderBytes.begin(), timeWaitingOrderBytes.end());
        bytes.insert(bytes.end(), idleTimeBytes.begin(), idleTimeBytes.end());

        this->_ipc->writeBytes(bytes);
    }

    void Kitchen::_sendReadyPizzas()
    {
        if (this->_readyPizzas.size()) {
            for (auto &pizza : this->_readyPizzas) {
                byte_v bytes;
                byte_v tmp;
                bytes.push_back(static_cast<char>(ORDER));
                bytes.push_back(static_cast<char>(pizza.getType()));
                bytes.push_back(static_cast<char>(pizza.getSize()));
                tmp = _numToBytes(pizza.getId());
                bytes.insert(bytes.end(), tmp.begin(), tmp.end());
                this->_ipc->writeBytes(bytes);
                this->_queueTime -= pizza.time() * this->_cookMul;
            }
            this->_readyPizzas.clear();
        }
    }

    int Kitchen::run()
    {
        while (this->isActive()) {
            this->_pollLoadBalancer();
            this->_sendPizzasToCook();
            auto readyPizzas = this->_cookManager->update(_computeDuration());
            this->_readyPizzas.insert(this->_readyPizzas.end(), readyPizzas.begin(), readyPizzas.end());
            for (size_t i = 0; i < readyPizzas.size(); i++) {
                this->_status.activeCooks--;
            }
            this->_updateStatus();
            this->_sendStatus();
            this->_sendReadyPizzas();
        _resetClock();
        }
        return 0;
    }

    Kitchen &Kitchen::operator<<(Pizza &pizza)
    {
        byte_v bytes;
        byte_v idAsBytes = this->_numToBytes(pizza.getId());

        bytes.push_back(static_cast<char>(Plazza::ORDER));
        bytes.push_back(static_cast<char>(pizza.getType()));
        bytes.push_back(static_cast<char>(pizza.getSize()));
        bytes.insert(bytes.end(), idAsBytes.begin(), idAsBytes.end());
        this->sendData(bytes);
        return *this;
    }

    Kitchen::Status Kitchen::getStatus() const
    {
        return _status;
    }

    void Kitchen::_pollLoadBalancer()
    {
        byte_v bytes;

        while (true) {
            bytes = this->pollData(3);
            if (!bytes.size()) {
                return;
            }
            if (bytes[0] == Plazza::ORDER) {
                PizzaType type = static_cast<PizzaType>(bytes[1]);
                PizzaSize size = static_cast<PizzaSize>(bytes[2]);
                bytes = this->pollData(sizeof(int));
                Pizza p(type, size, _bytesToNum(bytes));
                this->_queueTime += p.time() * this->_cookMul;
                this->_pizzaQueue.push(p);
            }
        }
    }

    void Kitchen::_pollKitchen()
    {
        byte_v bytes;
        PizzaType type;
        PizzaSize size;
        int id;

        while (true) {
            bytes = this->pollData(1);
            if (!bytes.size()) return;
            if (static_cast<int>(bytes[0]) == Plazza::ORDER) {
                bytes = this->pollData(2);
                type = static_cast<PizzaType>(bytes[0]);
                size = static_cast<PizzaSize>(bytes[1]);
                id = _bytesToNum(this->pollData(sizeof(int)));
                this->_readyPizzas.push_back(Pizza(type, size, id));
            } else if (static_cast<int>(bytes[0]) == Plazza::STATUS) {
                this->_status.activeCooks = this->_bytesToNum(this->pollData(sizeof(int)));
                this->_status.waitingOrders = this->_bytesToNum(this->pollData(sizeof(int)));
                this->_status.timeWaitingOrder = this->_bytesToNum(this->pollData(sizeof(float)));
                this->_status.idleTime = this->_bytesToNum(this->pollData(sizeof(float)));
            } else {
                throw std::runtime_error("Unknown message");
            }
        }
    }

    int Kitchen::_bytesToNum(byte_v bytes)
    {
        union integer converter;

        if (bytes.size() % sizeof(int))
            throw std::runtime_error("Can't convert bytes to int: invalid size");
        for (size_t i = 0; i < bytes.size(); i++) {
            converter.bytes[i % sizeof(int)] = bytes[i];
        }
        return converter.value;
    }

    byte_v Kitchen::_numToBytes(int val)
    {
        byte_v bytes;
        union integer converter;

        converter.value = val;
        for (size_t i = 0; i < sizeof(int); i++)
            bytes.push_back(converter.bytes[i]);
        return bytes;
    }

    byte_v Kitchen::_numToBytes(float val)
    {
        return _numToBytes(static_cast<int>(val));
    }

    byte_v Kitchen::_numToBytes(unsigned int val)
    {
        return _numToBytes(static_cast<int>(val));
    }

    pizza_v Kitchen::getReadyPizzas()
    {
        this->_pollKitchen();
        pizza_v pizzas = this->_readyPizzas;
        this->_readyPizzas.clear();
        return pizzas;
    }

    void Kitchen::_resetClock()
    {
        this->_kitchenClock = std::chrono::high_resolution_clock::now();
    }

    float Kitchen::_computeDuration()
    {
        high_res_clock newClock = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = newClock - this->_kitchenClock;
        return duration.count();
    }
} // namespace Plazza
