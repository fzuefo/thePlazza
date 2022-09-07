/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** IKitchen
*/

#pragma once
#include "Pizza.hpp"
namespace Plazza {
    class IKitchen {
        public:
            struct Status {
                unsigned int activeCooks;
                unsigned int waitingOrders;
                float timeWaitingOrder;
                float idleTime;
                bool operator<(const Status& s) const {
                    return (timeWaitingOrder < s.timeWaitingOrder);
                }
                bool operator>(const Status& s) const {
                    return (timeWaitingOrder > s.timeWaitingOrder);
                }
            };
            using pizza_v = std::vector<Pizza>;
            virtual ~IKitchen() = default;
            virtual void start() = 0;  //rajouter pour la coherence
            virtual IKitchen &operator<<(Pizza &pizza) = 0;
            virtual IKitchen::Status getStatus() const = 0;
            virtual pizza_v getReadyPizzas() = 0;
            virtual operator bool() const = 0;
    };
} // namespace Plazza
