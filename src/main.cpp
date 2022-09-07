/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#include "PlazzaCore.hpp"

int main(int ac, char **av)
{
    Plazza::ParseArg args;
    Plazza::Core::PlazzaCore plazza;

    if (ac != 4)
        return 84;
    if (!args.parse(av[1], av[2], av[3]))
        return 84;
    plazza.run(args);
    return 0;
}
