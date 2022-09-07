/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Pizza
*/

#pragma once
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace Plazza {

    struct Ingredients
    {
        int doe;
        int tomato;
        int gruyer;
        int ham;
        int mushroom;
        int steak;
        int goat;
        int egg;
        int love;
    };

    const std::map<std::string, size_t> sizes({
        std::pair("S", 1),
        std::pair("M", 2),
        std::pair("L", 4),
        std::pair("XL", 8),
        std::pair("XXL", 16)
    });

    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8,
    };

    const std::map<std::string, PizzaType> menu({
        std::pair("regina", Regina),
        std::pair("margarita", Margarita),
        std::pair("americana", Americana),
        std::pair("fantasia", Fantasia)
    });

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16,
    };

    class Pizza {
        public:
            Pizza();
            Pizza(std::string type, std::string size, int id);
            Pizza(PizzaType type, PizzaSize size, int id);
            ~Pizza();
            PizzaType getType() const;
            PizzaSize getSize() const;
            int getId() const;
            void setType(PizzaType type);
            void setSize(PizzaSize size);
            void setId(int id);

        /**
         * @brief get the pizza cooking time of himself
         * @return float but can be swap to a int
         */
        unsigned int time();

        /**
         * @brief get the righ componant for himself in the stock in reference
         * @details chec if he have the needed ingrediant, if NO ERROR else get them and substract them of the stock
         * @param a reference to a stock struct of kitchen
         * @return true if work
         * @return false if ERROR
         */
        bool getComponant(Ingredients &comp);

    private:
            int _id;
            PizzaType _type;
            PizzaSize _size;
            PizzaType _strToPizzaType(std::string &str);
            PizzaSize _strToPizzaSize(std::string &str);
    };

    inline std::string &operator<<(std::string &id, const Pizza& s) {
        id += std::to_string(s.getId()) + "/" + std::to_string(s.getType()) + "/" + std::to_string(s.getSize()) + ";";
        return (id);
    }

    inline std::ostream &operator<<(std::ostream &os, const Pizza& s)
    {
        os << "Una pizza ";
        for (auto &it : menu) {
            if (it.second == s.getType()) {
                os << it.first;
                break;
            }
        }
        os << std::string(" ");
        for (auto &it : sizes) {
            if (it.second == s.getSize()) {
                os << "size " << it.first;
                break;
            }
        }
        os << " for order n° " << s.getId();
        return os;
    }
}
