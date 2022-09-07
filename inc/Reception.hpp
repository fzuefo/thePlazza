/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#pragma once

#include "Pizza.hpp"
#include "Kitchen.hpp"
#include "IReception.hpp"
#include <vector>
#include <iostream>
#include <future>

namespace Plazza {
    class Reception: public IReception {
    public:
        Reception();
        ~Reception();
        std::vector<Request> getRequests(void) final;
        void sendResponse(Response) final;
        void update() final;
    protected:
    private:
        bool _isPrompt;
        std::vector<Response> _responses;
        std::future<std::string> _futureLine;
        std::vector<Request> _parseCommand(std::string &command, const int id);
        void _prompt();
    };
}

