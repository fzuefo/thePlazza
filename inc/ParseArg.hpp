/*
** EPITECH PROJECT, 2022
** B-CCP-400-LYN-4-1-theplazza-nicolas.saclier
** File description:
** ParseArg
*/

#ifndef PARSEARG_HPP_
#define PARSEARG_HPP_

#include <string>

namespace Plazza {
    class ParseArg {
        public:
            ParseArg();
            ParseArg(const std::string &mult, const std::string &cookNb,
                    const std::string &kitchenStock);
            ~ParseArg();
            bool parse(const std::string &mult, const std::string &cookNb,
                    const std::string &kitchenStock);
            bool isParsed() const;
            void reset();
            double getMult() const;
            unsigned long getCookNb() const;
            unsigned long getKitchenStock() const;

        private:
            bool _isNeg(const std::string &str);
            bool _isParsed;
            double _mult;
            unsigned long _cookNb;
            unsigned long _kitchenStock;
    };
}

#endif /* !PARSEARG_HPP_ */
