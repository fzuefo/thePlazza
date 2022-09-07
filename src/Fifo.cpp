/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Fifo
*/

#include "Fifo.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

namespace Plazza {
    Fifo::Fifo():
    _path("")
    {
    }

    Fifo::~Fifo()
    {
    }

    void Fifo::create(const std::string &path)
    {
        int status = mkfifo(path.c_str(), 0666);

        if (status == -1 && errno != EEXIST)
            throw std::runtime_error("Could not create fifo");
        _path = path;
    }

    void Fifo::destroy()
    {
        int status = remove(_path.c_str());
        if (status == -1)
            throw std::runtime_error("Could not destroy fifo");
    }

    void Fifo::open()
    {
        _file.open(_path, std::ios::in | std::ios::out);
        if (!_file.is_open())
            throw std::runtime_error("Could not open fifo");
    }

    void Fifo::close()
    {
        _file.close();
    }

    void Fifo::write(byte_v &bytes)
    {
        if (!_file.is_open())
            throw std::runtime_error("Fifo is closed");
        _file.write(bytes.data(), bytes.size());
        _file.flush();
        if (_file.bad())
            throw std::runtime_error("Could not write to fifo");
    }

    byte_v Fifo::read(size_t nbBytes)
    {
        byte_v bytes;
        char array[nbBytes] = {0};

        if (!_file.is_open())
            throw std::runtime_error("Fifo is closed");
        if (!_file.rdbuf()->in_avail())
            return bytes;
        _file.read(array, nbBytes);
        for (size_t i = 0; i < nbBytes; i++)
            bytes.push_back(array[i]);
        return bytes;
    }

    bool Fifo::isOpen() const
    {
        return _file.is_open();
    }

    bool Fifo::isEmpty()
    {
        return _file.peek() == std::ifstream::traits_type::eof();
    }

} // namespace Plazza