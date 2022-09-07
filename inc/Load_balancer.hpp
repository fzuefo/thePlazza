/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** loop prime of plaza
*/

#pragma once
#include <string>
#include <memory>
#include <vector>

#include "Pizza.hpp"
#include "IKitchen.hpp"
#include "IReception.hpp"
#include "Kitchen.hpp"
#include "ParseArg.hpp"


namespace Plazza {
    namespace Core {
        class Load_balancer {
        public:
            Load_balancer(const ParseArg &args);
            ~Load_balancer();
            void run();

        private:
            bool _isRun;
            int _max;
            const ParseArg _args;
            std::vector<std::shared_ptr<Plazza::IKitchen>> _kitchens;
            std::vector<std::shared_ptr<Plazza::Pizza>> _pizzaOrders;
            std::shared_ptr<Plazza::IReception> _reception;

            bool test_full();
            void balance_pizza();
            void add_pizza(Plazza::Pizza obj);
            void getOrders();
            void launch_new_kitchen();
            void sendKitchenStatus();
            std::string poll_kitchens();
            void _sendReadyPizzas();
            void _clearUnusedKitchens();
            /**
             * @brief get the kitechen with the smalest time waiting.
             * @return ID of the prosse with the smallest Q
            */
            int getSmllPross();
            bool _isFull(const int &i);
        };

    }
}
