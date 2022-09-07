/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** PlazzaIpc
*/

#pragma once
#include <string>
#include <cstdio>
#include <memory>
#include "AIPC.hpp"
#include "Fifo.hpp"

namespace Plazza {
    class PlazzaIpc: public AIPC {
        public:
            PlazzaIpc();
            ~PlazzaIpc();
            void writeBytes(byte_v bytes) override;
            byte_v readBytes(size_t nbBytes) override;
            bool isEmpty(void) override;
            void open(void) override;
            bool isOpen(void) const override;
            void close(void) override;
        protected:
        private:
            unsigned int _id;
            std::unique_ptr<Fifo> _parentReadFifo;
            std::unique_ptr<Fifo> _childReadFifo;
    };
} // namespace Plazza


