/*
** EPITECH PROJECT, 2022
** include
** File description:
** thread header
*/

#ifndef COOK_H_
#define COOK_H_

#include "Pizza.hpp"
#include <thread>
#include <mutex>
#include <memory>

namespace Plazza
{


    /**
     * @class Cook_manager
     * @brief Encapsulation of threading for the Kitchen
     * @details manage is memory, (no zombi will be release),
     * @Warning Using a timer for syncronise but don't have intern Clock
     * @see Plazza::Kitchen
     */
    class Cook_manager {
    public:
        Cook_manager(unsigned int maxCooks, unsigned int reloadTime, double mul);
        ~Cook_manager();

        /**
         * @brief the manager will split the pizza work to is cooker
         * @details will automaticalie assign the pizza to a cooker(thread).
         * @warning Non-blocking function
         * @return false if the cook are all occupie
         * @return true if work
         */
        bool manag_pizza(Plazza::Pizza piza);

        /**
         * @brief update the global of the kitchen
         * @param take the time actual in float
         * @return a vector with all id of pizza who are cooked
         */
        std::vector<Plazza::Pizza> update(float time);

        /**
         * @brief test if the cook are full
         * @return true if full
         */
        bool isFull();

        /**
         * @brief Get the Nb Active Cooks
         * @return unsigned int
         */
        unsigned int getNbActiveCooks() const;

    private:
        void add_pizza(Plazza::Pizza piza);
        void add_ingredient();
        void chec_cookActive();
        unsigned int _max;
        int _reload;
        double _mul;
        std::vector<std::thread> _Cook;
        std::vector<Plazza::Pizza> _cooked_pizza_id;
        std::vector<std::shared_ptr<float>> _delta_t;
        Ingredients _item;
        float _elaps;
        float _delta;
        bool _isActive;
    };
}




#endif
