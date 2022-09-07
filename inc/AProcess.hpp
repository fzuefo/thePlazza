/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** AProcess
*/

#pragma once
#include "IProcess.hpp"
#include "PlazzaIpc.hpp"
#include <unistd.h>

namespace Plazza {
    /**
     * @brief AProcess implements some methods to manage processes
     * @details The developper now only needs to implement the run() method
     */
    class AProcess: public IProcess {
        public:
            AProcess();
            ~AProcess() override;
            void start() override;
            bool isParent(void) const final;
            bool isChild(void) const final;
            bool isActive(void) const final;
            pid_t getPid(void) const final;
            void sendData(byte_v &) final;
            byte_v pollData(size_t nbBytes) final;
            void setIpc(std::shared_ptr<IIPC> ipc) final;

        protected:
            /**
             * @brief Run is the function that will be called once the process is forked.
             * @details The developper must implement this method as the main function of the process
             * @return The exit code of the process
             */
            virtual int run(void) = 0;
            std::shared_ptr<IIPC> _ipc;
        private:
            pid_t _pid;
    };
}
