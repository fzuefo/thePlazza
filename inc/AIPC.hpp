/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** AIPC
*/

#pragma once
#include "IIPC.hpp"

namespace Plazza {

    /**
     * @brief Abstract IPC from which all IPCs inherit
     * @details This abstract class implements the setMode() method
     */
    class AIPC: public IIPC {
        public:
            virtual ~AIPC() = default;
            void setMode(IPCMode mode) final;
        protected:
            IPCMode _mode;
        private:
    };

}