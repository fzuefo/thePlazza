/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Fifo
*/

#pragma once
#include <vector>
#include <string>
#include <fstream>

namespace Plazza {
    using byte_v = std::vector<char>;
    class Fifo {
        public:
            Fifo();
            ~Fifo();
            void create(const std::string &path);
            void destroy();
            void open();
            bool isOpen() const;
            void close();
            void write(byte_v &bytes);
            bool isEmpty();
            byte_v read(size_t nbBytes);
        private:
            std::string _path;
            std::fstream _file;
    };
}

