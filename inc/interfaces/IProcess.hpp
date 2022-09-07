/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** IProcess
*/

#pragma once

#include <memory>
#include <vector>
#include "AIPC.hpp"

namespace Plazza {
    using byte_v = std::vector<char>;


    /**
     * @brief IProcess
     * @details Processes launched by main loop must inherit of this class.
     * @see IIPC
     */
    class IProcess {
        public:
            virtual ~IProcess() = default;
            /**
             * @brief Fork process and call run()
             * Dont forget to check your pid!
             */
            virtual void start(void) = 0;

            /**
             * @brief Format the Process::Message using it's class methods into a byte vector, and call IIPC.writeBytes()
             *
             */
            virtual void sendData(byte_v &) = 0;

            /**
             * @brief Call IIPCS.readBytes, and format into Process::Message using it's class methods.
             *
             * @return Message_ptr
             */
            virtual byte_v pollData(size_t nbBytes) = 0;

            /**
             * @brief Check if process is the parent
             *
             * @return true
             * @return false
             */
            virtual bool isParent(void) const = 0;

            /**
             * @brief Check if process is the child
             *
             * @return true
             * @return false
             */
            virtual bool isChild(void) const = 0;

            /**
             * @brief Get the pid value
             *
             * @return pid_t
             */
            virtual pid_t getPid(void) const = 0;

            /**
             * @brief Check if process is active (useful for child processes)
             * @details If process is not active, it means it has been sent SIGINT
             * The child process needs to clean up its resources and exit.
             * @return true if active
             * @return false
             */
            virtual bool isActive(void) const = 0;

            virtual void setIpc(std::shared_ptr<IIPC> ipc) = 0;
    };

} // namespace Plazza
