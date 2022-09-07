/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** IReception
*/

#pragma once

#include "Pizza.hpp"
#include "IKitchen.hpp"
#include <vector>

namespace Plazza {


    enum RequestType {
        ORDER,
        STATUS,
        QUIT
    };
    /**
     * @brief Requests are the parsed inputs from the user.
     * @details Requests can be either a Pizza, or one of 2 commands: "quit" or "status".
     */
    struct Request {
        RequestType type;
        Pizza pizza;
    };


    typedef RequestType ResponseType;

    /**
     * @brief Response represents the feedback the program sends to the user.
     * @details Responses can be either a Pizza, or a representation of the kitchens' statuses.
     * @see IKitchen::Status
     */
    struct Response {
        ResponseType type;
        std::vector<IKitchen::Status> kitchenStatuses;
        std::vector<Pizza> pizzas;
    };

/**
 * @class IReception
 * @brief IReception represents the user interface.
 * @details It must be totally non blocking, as the Load Balancer will run in the same loop.
 * @see https://gist.github.com/vmrob/ff20420a20c59b5a98a1
 */
    class IReception {
        public:
            virtual ~IReception(void) = default;

            /**
             * @brief Get the Request from the user.
             * @warning This method must be non-blocking
             * @return Reception::Request
             */
            virtual std::vector<Request> getRequests(void) = 0;

            /**
             * @brief Send the reponse to the user
             * @param Response
             */
            virtual void sendResponse(Response) = 0;

             /**
             * @brief update the graphic or any logical interphace (terminal, ncurses ..)
             * @details need to be call before any GET and after any SEND
             * @param string of the pizza who end: "ID/TYPE/SIZE;ID/TYPE/SIZE; etc..."
             */
            virtual void update() = 0;


    };
} // namespace Plazza
