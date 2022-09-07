/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Pizza
*/

#include "Pizza.hpp"

namespace Plazza {

    static const std::map<PizzaType, unsigned int> cookingTimes({
        std::pair(Regina, 2),
        std::pair(Margarita, 1),
        std::pair(Americana, 2),
        std::pair(Fantasia, 4)
    });

    Pizza::Pizza()
    {}

    Pizza::Pizza(std::string type, std::string size, int id):
    _id(id), _type(_strToPizzaType(type)), _size(_strToPizzaSize(size))
    {}

    Pizza::Pizza(PizzaType type, PizzaSize size, int id):
    _id(id), _type(type), _size(size)
    {}


    PizzaType Pizza::_strToPizzaType(std::string &str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        if (menu.find(str) == menu.end())
            throw std::invalid_argument("This pizza is not on the menu: " + str);
        return static_cast<PizzaType>(menu.at(str));
    }

    PizzaSize Pizza::_strToPizzaSize(std::string &str)
    {
        if (sizes.find(str) == sizes.end())
            throw std::invalid_argument("This size does not exist: " + str);
        return static_cast<PizzaSize>(sizes.at(str));
    }

    Pizza::~Pizza()
    {}

    PizzaType Pizza::getType() const
    {
        return _type;
    }

    PizzaSize Pizza::getSize() const
    {
        return _size;
    }

    int Pizza::getId() const
    {
        return _id;
    }

    void Pizza::setType(PizzaType type)
    {
        _type = type;
    }

    void Pizza::setSize(PizzaSize size)
    {
        _size = size;
    }

    void Pizza::setId(int id)
    {
        _id = id;
    }

    bool Pizza::getComponant(Plazza::Ingredients &comp)
    {
        Plazza::PizzaType type = this->getType();

        if (comp.doe == 0 || comp.tomato == 0)
            return false;
        switch (type) {
        case Plazza::Regina:
            if (comp.gruyer == 0)
                return false;
            else {
                comp.doe--;
                comp.gruyer--;
                comp.tomato--;
                return true;
            }
        case PizzaType::Margarita:
            if (comp.gruyer == 0 || comp.mushroom == 0 || comp.ham == 0)
                return false;
            else {
                comp.doe--;
                comp.gruyer--;
                comp.tomato--;
                comp.mushroom--;
                comp.ham--;
                return true;
            }
            
        case PizzaType::Americana:
            if (comp.gruyer == 0 || comp.steak == 0)
                return false;
            else {
                comp.doe--;
                comp.gruyer--;
                comp.steak--;
                comp.tomato--;
                return true;
            }
        case PizzaType::Fantasia:
            if (comp.goat == 0 || comp.egg == 0 || comp.love == 0)
                return false;
            else {
                comp.doe--;
                comp.goat--;
                comp.tomato--;
                comp.egg--;
                comp.love--;
                return true;
            }

        }
        return false;
    }

    unsigned int Pizza::time(){
        return cookingTimes.at(this->getType());
    }
}
