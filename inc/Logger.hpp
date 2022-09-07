/*
** EPITECH PROJECT, 2022
** B-CCP-400-LYN-4-1-theplazza-nicolas.saclier
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include "Pizza.hpp"
#include "Kitchen.hpp"

namespace Plazza {
 
    class Logger {
        public:
            Logger();
            ~Logger();
            Logger &operator<<(const std::string &message);
            Logger &operator<<(const char *message);
            Logger &operator<<(const size_t &message);
            Logger &operator<<(const Pizza &message);
            Logger &operator<<(const IKitchen::Status &message);
        
        private:
            std::ofstream _file;
    };

    static Logger logger;
}

#endif /* !LOGGER_HPP_ */
