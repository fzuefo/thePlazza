/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Kitchen
*/

#pragma once

#include "AProcess.hpp"
#include "Pizza.hpp"
#include "IKitchen.hpp"
#include "Cook.hpp"
#include <queue>
#include <iostream>

namespace Plazza {

    using int_v = std::vector<int>;
    using byte_v = std::vector<char>;
    using high_res_clock = std::chrono::time_point<std::
    chrono::high_resolution_clock>;

    class Kitchen: public AProcess, public IKitchen {
        public:
            Kitchen(unsigned long maxCooks, unsigned long reloadTime, double mul);
            ~Kitchen();
            int run() final;
            void start() override;
            Kitchen &operator<<(Pizza &pizza) final;
            IKitchen::Status getStatus() const final;
            pizza_v getReadyPizzas() final;
        operator bool() const final {
            if (2 * _maxCooks - 1 <= _status.activeCooks + _status.waitingOrders)
                return (true);
            return false;
        }
        private:
            unsigned int _maxCooks;
            unsigned int _reloadTime;
        double _cookMul;
        std::unique_ptr<Cook_manager> _cookManager;
            float _queueTime;
            std::queue<Pizza> _pizzaQueue;
            pizza_v _readyPizzas;
            IKitchen::Status _status;
            high_res_clock _kitchenClock;
            void _pollKitchen();
            void _pollLoadBalancer();
            void _sendPizzasToCook();
            int _bytesToNum(byte_v);
            void _updateStatus();
            float _computeDuration();
            void _resetClock();
            void _sendStatus();
            void _sendReadyPizzas();
            byte_v _numToBytes(int);
            byte_v _numToBytes(float);
            byte_v _numToBytes(unsigned int);
            struct Response {
                pizza_v pizzas;
                Status status;
            };
            union integer {
                int value;
                char bytes[sizeof(int)];
            };
    };

    inline std::ostream &operator<<(std::ostream &os, const IKitchen::Status &status)
    {
        os << "Active cooks: " << status.activeCooks << std::endl;
        os << "Waiting orders: " << status.waitingOrders << std::endl;
        os << "Time to completion: " << status.timeWaitingOrder << std::endl;
        os << "Idle time: " << status.idleTime << std::endl;
        return os;
    }
} // namespace Plazza

