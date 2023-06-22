#include "ClientClass.hpp"

void ClientClass::onEvent(SDL_Event* ev)
{
#ifdef _CLIENT_DEBUG_
    std::cout << "void ClientClass::onEvent(SDL_Event* ev)\n";
#endif // _SERVER_DEBUG_

    ClassEvent::onEvent(ev);
}

void ClientClass::onExit()
{
#ifdef _CLIENT_DEBUG_
    std::cout << "void ClientClass::onExit()\n";
#endif // _SERVER_DEBUG_

    this->running = false;
}

void ClientClass::onTextInput(char* text)
{
#ifdef _CLIENT_DEBUG_
    std::cout << "void ClientClass::onTextInput(char* text)\n";
#endif // _SERVER_DEBUG_

    if (this->msgHistory.empty())
        this->msgHistory.push_back(std::string());

    if (this->sending && this->sendMessage.length() <= 500)
    {
        this->sendMessage += text;
        if (this->sendMessage[0] == ' ')
            this->sendMessage = "";
        std::string r = this->sendMessage;
        this->msgHistory[this->msgHistory.size() - 1] =
            this->timeStamp + "Client: " + r;
    }
}

void ClientClass::onReturn()
{
#ifdef _CLIENT_DEBUG_
    std::cout << "void ClientClass::onReturn()\n";
#endif // _SERVER_DEBUG_

    if (this->sending) //send
    {
        if (!this->sendMessage.empty())
        {
            this->fout << this->sendMessage.c_str() << "\n";
            this->SendMsg();
        }
    }
}

void ClientClass::onBackspace()
{
#ifdef _CLIENT_DEBUG_
    std::cout << "void ClientClass::onBackspace()\n";
#endif // _SERVER_DEBUG_

    if (this->sending)
    {
        if (!this->sendMessage.empty())
        {
            this->sendMessage.pop_back();
            this->msgHistory[this->msgHistory.size() - 1] =
                this->timeStamp + "Client: " + this->sendMessage;
        }
    }
}
