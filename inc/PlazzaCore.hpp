/*
** EPITECH PROJECT, 2022
** B-CCP-400-LYN-4-1-theplazza-nicolas.saclier
** File description:
** PlazzaCore
*/

#ifndef PLAZZACORE_HPP_
#define PLAZZACORE_HPP_

#include "ParseArg.hpp"
#include "Load_balancer.hpp"

namespace Plazza {

    namespace Core {

        class PlazzaCore {

            public:
                PlazzaCore();
                ~PlazzaCore();
                void run(const ParseArg &args);
        };

    }
    
}

#endif /* !PLAZZACORE_HPP_ */
