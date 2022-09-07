/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** IIPC
*/

#pragma once

#include <vector>
#include <cstddef>

namespace Plazza {
    using byte_v = std::vector<char>;

    enum IPCMode {
        PARENT,
        CHILD
    };

    /**
     * @brief IIPC or Inter Process Communication
     * @details This class is used to communicate between processes
     */
    class IIPC {
        public:
            virtual ~IIPC(void) = default;

            /**
             * @brief write a byte vector into the desired protocol (IP, named pipes, etc)
             *
             * @param bytes
             */
            virtual void writeBytes(byte_v bytes) = 0;

            /**
             * @brief Get a byte vector from the desired protocol (IP, named pipes, etc)
             *
             * @param bytes
             */
            virtual byte_v readBytes(size_t nbBytes) = 0;

            /**
             * @brief Check if there are bytes to read
             *
             * @return true
             * @return false
             */
            virtual bool isEmpty(void) = 0;

            /**
             * @brief Open the communication channel
             */
            virtual void open(void) = 0;

            /**
             * @brief Check if communication channel is open
             * @return true if open
             * @return false if closed
             */
            virtual bool isOpen(void) const = 0;

            /**
             * @brief Close the communication channel
             */
            virtual void close(void) = 0;

            /**
             * @brief Set the communication mode
             * @details PARENT or CHILD. PARENT is the parent process, CHILD is the child process
             * @param mode
             * @see IPCMode
             */
            virtual void setMode(IPCMode mode) = 0;
    };
} // namespace Plazza
