/*
** EPITECH PROJECT, 2022
** laod_balancer.cpp
** File description:
** plaza
*/

#include "Load_balancer.hpp"
#include "Reception.hpp"

namespace Plazza {

    namespace Core {

        Load_balancer::Load_balancer(const ParseArg &args)
        :_isRun(true), _args(args), _reception(std::make_shared<Reception>())
        {
            _max = _args.getCookNb();
        }

        Load_balancer::~Load_balancer(){}

        void Load_balancer::run()
        {
            while (_isRun) {
                this->getOrders();
                if (!_pizzaOrders.empty())
                    this->balance_pizza();
                this->_sendReadyPizzas();
                this->_reception->update();
                this->_clearUnusedKitchens();
            }
        }

        void Load_balancer::_clearUnusedKitchens()
        {
            for (auto it = _kitchens.begin(); it != _kitchens.end();) {
                if (it->get()->getStatus().idleTime >= 5000) {
                    it = _kitchens.erase(it);
                } else {
                    ++it;
                }
            }
        }

        std::string Load_balancer::poll_kitchens()
        {
            std::string id = "";
            std::vector<Pizza> pizzas;

            for (size_t i = 0; i < _kitchens.size(); i++) {
                pizzas = _kitchens[i]->getReadyPizzas();
                if (!pizzas.empty()) {
                    for (size_t j = 0; j < pizzas.size(); j++)
                        id << pizzas[j];
                }
            }
            return (id);
        }

        void Load_balancer::_sendReadyPizzas()
        {
            std::vector<Pizza> pizzas;
            Response response;

            response.type = Plazza::ORDER;
            for (auto &it: _kitchens) {
                pizzas = it->getReadyPizzas();
                response.pizzas.insert(response.pizzas.end(), pizzas.begin(), pizzas.end());
            }
            _reception->sendResponse(response);
        }

        void Load_balancer::getOrders()
        {
            std::vector<Plazza::Request> requests = this->_reception->getRequests();

            for (auto it: requests) {
                if (it.type == Plazza::ORDER)
                    this->add_pizza(it.pizza);
                else if (it.type == Plazza::STATUS)
                    this->sendKitchenStatus();
                else
                    _isRun = false;
            }
        }

        void Load_balancer::add_pizza(Plazza::Pizza obj)
        {
            this->_pizzaOrders.push_back(std::make_shared<Plazza::Pizza>(obj));
        }

        void Load_balancer::sendKitchenStatus()
        {
            Plazza::Response rep;

            rep.type = Plazza::STATUS;
            for (size_t i = 0; i < _kitchens.size(); i++)
                rep.kitchenStatuses.push_back(this->_kitchens[i]->getStatus());
            this->_reception->sendResponse(rep);
        }

        void Load_balancer::balance_pizza()
        {
            int index = 0;

            if (_kitchens.empty()) {
                this->launch_new_kitchen();
            }
            for (auto &pizza: this->_pizzaOrders) {
                this->_sendReadyPizzas();
                test_full();
                index = getSmllPross();
                *this->_kitchens[index].get() << *pizza.get();
            }
            this->_pizzaOrders.clear();
        }

        bool Load_balancer::test_full()
        {
            for (size_t i = 0; i < _kitchens.size(); i++) {
                if (!(_isFull(i))) {
                    return false;
                }
            }
            this->launch_new_kitchen();
            return true;
        }

        int Load_balancer::getSmllPross()
        {
            IKitchen::Status tmp;
            IKitchen::Status mem;
            int index = 0;

            for (size_t  i = 0; i < _kitchens.size(); i++) {
                tmp = this->_kitchens[i]->getStatus();
                if (i == 0)
                    mem = tmp;
                else {
                    if (tmp < mem) {
                        mem = tmp;
                        index = i;
                    }
                }
            }
            return (index);
        }

        void Load_balancer::launch_new_kitchen()
        {
            std::shared_ptr<Plazza::IKitchen> obj;

            obj = std::make_shared<Plazza::Kitchen>(_args.getCookNb(),
            _args.getKitchenStock(), _args.getMult());
            obj->start();
            _kitchens.push_back(obj);
        }

        bool Load_balancer::_isFull(const int &i)
        {
            return (_kitchens[i]->getStatus().waitingOrders +
            _kitchens[i]->getStatus().activeCooks
            >= static_cast<unsigned int>(_max * 2));
        }

    }
}
