/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include <regex>
#include <future>
#include "Logger.hpp"

namespace Plazza {

    std::string getlineCin()
    {
        std::string line;
        std::getline(std::cin, line);
        return line;
    }

    Reception::Reception():
    _isPrompt(false)
    {
        Plazza::logger << "Welcoma to la Plazza da Gino! What do you wanta to eata?\n";
    }

    Reception::~Reception()
    {
        Plazza::logger << "\nMamma mia, it'sa gettinga late! Gooda Bye!\n" ;
    }

    void Reception::_prompt()
    {
        if (this->_isPrompt) return;

        this->_futureLine = std::async(std::launch::async, getlineCin);
        std::cout << "> ";
        this->_isPrompt = true;
    }

    std::vector<Request> Reception::getRequests()
    {
        static int id = 0;
        std::string command;
        std::vector<Request> reqs;

        this->_prompt();
        if (this->_futureLine.wait_for(std::chrono::milliseconds(20)) != std::future_status::ready)
            return reqs;
        id++;
        std::string line;
        if (!std::cin) {
            Request r = {.type = RequestType::QUIT, .pizza = Pizza()};
            reqs.push_back(r);
            return reqs;
        }
        line = this->_futureLine.get();
        std::stringstream lineStream(line);
        while (getline(lineStream, command, ';')) {
            try {
                std::vector<Request> commandReqs = this->_parseCommand(command, id);
                reqs.insert(reqs.end(), commandReqs.begin(), commandReqs.end());
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
        this->_isPrompt = false;
        return reqs;
    }

    std::vector<Request> Reception::_parseCommand(std::string &command, const int id)
    {
        std::regex statusRegex("^\\s*status\\s*$");
        std::regex orderRegex("^\\s*([a-zA-Z]+)\\s+(S|M|L|XL|XXL)\\s+x([1-9][0-9]*)\\s*$");
        std::smatch m;
        std::vector<Request> reqs;
        size_t nb_pizza = 0;

        if (std::regex_search(command, m, statusRegex)) {
            Request r {.type = STATUS, .pizza = Pizza()};
            reqs.push_back(r);
            return reqs;
        }
        if (!std::regex_search(command, m, orderRegex))
            throw std::runtime_error("Invalid command: " + command);
        nb_pizza = std::stoi(m[3]);
        for (size_t i = 0; i < nb_pizza; i++) {
            Request r {.type = ORDER, .pizza = Pizza(m[1], m[2], id)};
            reqs.push_back(r);
        }
        return reqs;
    }

    void Reception::sendResponse(Plazza::Response res)
    {
        this->_responses.push_back(res);
    }

    void Reception::update()
    {
        if (this->_responses.empty()) return;
        for (auto &res: this->_responses) {
            if (res.type == Plazza::ORDER) {
                for (auto &it: res.pizzas) {
                    Plazza::logger << it << "\n";
                }
                if (res.pizzas.size()) {
                    (std::cout << "> ").flush();
                }
            } else if (res.type == Plazza::STATUS) {
                Plazza::logger << "*** STATUS ***" << "\n";
                Plazza::logger << "Active Kitchens: " << res.kitchenStatuses.size() << "\n";
                for (size_t i = 0; i < res.kitchenStatuses.size(); i++) {
                    Plazza::logger << "Kitchen " << i << ":" << "\n";
                    Plazza::logger << res.kitchenStatuses[i] << "\n";
                }
            }
        }
        this->_responses.clear();
    }
}
