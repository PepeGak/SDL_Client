#include "ClientClass.hpp"

void ClientClass::onLoop()
{
#ifdef _CLIENT_DEBUG_
    std::cout << "void ClientClass::onLoop()\n";
#endif // _SERVER_DEBUG_

    if (!this->sending) //recv
    {
        char* buf = new char[512];
        ZeroMemory(buf, 512);
        int result = recv(this->ConnectSocket, buf, 512, 0);
        this->recvMessage = buf;
        delete[] buf; buf = nullptr;

        std::string r;
        if (result == 0)
        {
            this->msgHistory.push_back("Connection terminated");
            this->onExit();
            return;
        }
        if (result < 0)
        {
            this->msgHistory.push_back("ClientClass::onLoop() recv error");
            this->onExit();
            return;
        }

        r = this->GetTime() + "Server: " + this->recvMessage;
        this->msgHistory.push_back(r); //будем потом отображать в ServerClass::onRender()
        this->timeStamp = this->GetTime();
        this->msgHistory.push_back(this->timeStamp + "Client: ");
        this->sending = true;
        if (this->recvMessage == "#")
        {
            this->msgHistory.push_back("Connection terminated");
            this->onExit();
            return;
        }
    }
}
