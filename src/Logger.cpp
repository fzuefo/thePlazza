/*
** EPITECH PROJECT, 2022
** B-CCP-400-LYN-4-1-theplazza-nicolas.saclier
** File description:
** Logger
*/

#include "Logger.hpp"

namespace Plazza {

    Logger::Logger()
    {
        _file.open("log.txt");
    }

    Logger::~Logger()
    {
        if (_file) {
            _file.close();
        }
    }

    Logger &Logger::operator<<(const std::string &message)
    {
        std::cout << message;
        if (_file) {
            _file << message;
            _file.flush();
        }
        return *this;
    }

    Logger &Logger::operator<<(const char *message)
    {
        std::string newMessage(message);

        std::cout << newMessage;
        if (_file) {
            _file << message;
            _file.flush();
        }
        return *this;
    }

    Logger &Logger::operator<<(const size_t &message)
    {
        std::cout << message;
        if (_file) {
            _file << message;
            _file.flush();
        }
        return *this;
    }

    Logger &Logger::operator<<(const Pizza &message)
    {
        std::cout << message;
        if (_file) {
            _file << message;
            _file.flush();
        }
        return *this;
    }

    Logger &Logger::operator<<(const IKitchen::Status &message)
    {
        std::cout << message;
        if (_file) {
            _file << message;
            _file.flush();
        }
        return *this;
    }


}
