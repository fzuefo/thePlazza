/*
** EPITECH PROJECT, 2022
** B-CCP-400-LYN-4-1-theplazza-nicolas.saclier
** File description:
** PlazzaCore
*/

#include "PlazzaCore.hpp"

namespace Plazza {

    namespace Core {

        PlazzaCore::PlazzaCore()
        {

        }

        PlazzaCore::~PlazzaCore()
        {

        }

        void PlazzaCore::run(const ParseArg &args) {
            Plazza::Core::Load_balancer load_balancer(args);

            load_balancer.run();
        }
    }
}
