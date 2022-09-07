/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Process
*/

#include "AProcess.hpp"
#include <unistd.h>
#include <signal.h>

/* !!!!!!!!!!!!!!!!!

   attention l'erreur isActive est une fonction que se mettais en conflic avec la global isActive 
      - pour ma compile test jai degager le E a la fin des isActive (variable)

 !!!!!!!!!!!!!*/
namespace Plazza {

    static volatile bool isActiv = true;

    static void sigHandler(int sig)
    {
        (void)sig;
        isActiv = false;
    }

    AProcess::AProcess()
    {
    }

    AProcess::~AProcess()
    {
        if (_pid == 0)
            return;
        kill(_pid, SIGINT);
    }

    void AProcess::start()
    {
        _pid = fork();
        if (_pid == 0) {
            signal(SIGINT, sigHandler);
            this->_ipc->setMode(IPCMode::CHILD);
            exit(this->run());
        }
        this->_ipc->setMode(IPCMode::PARENT);
    }

    void AProcess::setIpc(std::shared_ptr<IIPC> ipc)
    {
        this->_ipc = std::move(ipc);
    }

    bool AProcess::isParent() const
    {
        return _pid != 0;
    }

    bool AProcess::isChild() const
    {
        return _pid == 0;
    }

    pid_t AProcess::getPid() const
    {
        return _pid;
    }

    bool AProcess::isActive() const
    {
        return isActiv;
    }

    void AProcess::sendData(byte_v &data)
    {
        _ipc->writeBytes(data);
    }

    byte_v AProcess::pollData(size_t nbBytes)
    {
        return _ipc->readBytes(nbBytes);
    }
}
