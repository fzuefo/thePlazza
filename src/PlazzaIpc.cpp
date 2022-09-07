/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** PlazzaIpc
*/

#include "PlazzaIpc.hpp"
#include <set>
#include <iostream>
#include <unistd.h>

namespace Plazza {

    static std::set<unsigned int> ids;

    PlazzaIpc::PlazzaIpc():
    _id(0)
    {
        pid_t pid = getpid();

        while (ids.find(_id) != ids.end())
            _id++;
        this->_parentReadFifo = std::make_unique<Fifo>();
        this->_childReadFifo = std::make_unique<Fifo>();
        this->_parentReadFifo->create("/tmp/plazza_parent_read_" + std::to_string(pid) + "_" + std::to_string(_id));
        this->_childReadFifo->create("/tmp/plazza_child_read_" + std::to_string(pid) + "_" + std::to_string(_id));
    }

    PlazzaIpc::~PlazzaIpc()
    {
        this->_parentReadFifo->destroy();
        this->_childReadFifo->destroy();
        ids.erase(this->_id);
    }

    void PlazzaIpc::open()
    {
        this->_parentReadFifo->open();
        this->_childReadFifo->open();
    }

    bool PlazzaIpc::isOpen() const
    {
        return this->_parentReadFifo->isOpen() && this->_childReadFifo->isOpen();
    }

    bool PlazzaIpc::isEmpty()
    {
        if (this->_mode == IPCMode::PARENT)
            return this->_childReadFifo->isEmpty();
        else
            return this->_parentReadFifo->isEmpty();
    }

    void PlazzaIpc::close()
    {
        this->_parentReadFifo->close();
        this->_childReadFifo->close();
    }

    void PlazzaIpc::writeBytes(byte_v bytes)
    {
        if (this->_mode == IPCMode::PARENT) {
            this->_childReadFifo->write(bytes);
        }
        else {
            this->_parentReadFifo->write(bytes);
        }
    }

    byte_v PlazzaIpc::readBytes(size_t nbBytes)
    {
        if (this->_mode == IPCMode::PARENT) {
            return this->_parentReadFifo->read(nbBytes);
        }
        return this->_childReadFifo->read(nbBytes);
    }
}
