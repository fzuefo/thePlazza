/*
** EPITECH PROJECT, 2022
** B-CCP-400-LYN-4-1-theplazza-nicolas.saclier
** File description:
** ParseArg
*/

#include "ParseArg.hpp"
#include <iostream>

namespace Plazza {
    ParseArg::ParseArg()
    {
        reset();
    }

    ParseArg::ParseArg(const std::string &mult, const std::string &cookNb,
                        const std::string &kitchenStock)
    {
        reset();
        parse(mult, cookNb, kitchenStock);
    }

    ParseArg::~ParseArg()
    {

    }

    bool ParseArg::parse(const std::string &mult, const std::string &cookNb,
                                const std::string &kitchenStock)
    {
        try {
            if (_isNeg(mult) || _isNeg(cookNb) || _isNeg(kitchenStock))
                throw std::invalid_argument("Negative number");
            _mult = std::stod(mult);
            _cookNb = std::stoul(cookNb);
            _kitchenStock = std::stoul(kitchenStock);
        } 
        catch(const std::invalid_argument& e) {
            std::cerr << "Invalid Argument\0" << std::endl;
            reset();
            _isParsed = false;
            return _isParsed;
        }
        _isParsed = true;
        return _isParsed;
    }

    bool ParseArg::isParsed() const
    {
        return _isParsed;
    }

    void ParseArg::reset()
    {
        _mult = 0;
        _cookNb = 0;
        _kitchenStock = 0;
    }

    double ParseArg::getMult() const
    {
        return _mult;
    }

    unsigned long ParseArg::getCookNb() const
    {
        return _cookNb;
    }

    unsigned long ParseArg::getKitchenStock() const
    {
        return _kitchenStock;
    }

    bool ParseArg::_isNeg(const std::string &str)
    {
        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] == '-')
                return true;
        }
        return false;
    }
}
