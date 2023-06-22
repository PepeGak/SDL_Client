#include "ClientClass.hpp"

ClientClass::ClientClass()
{
#ifdef _CLIENT_DEBUG_
    std::cout << "ClientClass::ServerClass()\n";
#endif // _SERVER_DEBUG_

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    this->version = MAKEWORD(2, 2);
    this->addrResult = nullptr;
    this->ConnectSocket = INVALID_SOCKET;
    ZeroMemory(&this->hints, sizeof(this->hints));
    this->hints.ai_family = AF_INET;
    this->hints.ai_socktype = SOCK_STREAM;
    this->hints.ai_protocol = IPPROTO_TCP;
    this->hints.ai_flags = AI_PASSIVE;

    this->window = nullptr;
    this->windowSurf = nullptr;
    this->background = nullptr;
    this->font = nullptr;
    this->icon = nullptr;

    this->running = true;
    this->sending = true;
}

ClientClass::~ClientClass()
{
#ifdef _CLIENT_DEBUG_
    std::cout << "ClientClass::~ServerClass()\n";
#endif // _SERVER_DEBUG_

    this->onQuit();
}

int ClientClass::onExecute()
{
#ifdef _CLIENT_DEBUG_
    std::cout << "int ClientClass::onExecute()\n";
#endif // _SERVER_DEBUG_

    if (!this->onInit())
    {
        this->onQuit();
        return -1;
    }
    
    this->msgHistory.push_back("Connection established. Enjoy your chat.");
    this->timeStamp = this->GetTime();
    this->msgHistory.push_back(this->timeStamp + "Client: ");
    
    SDL_Event ev;
    while (this->running)
    {
        while (SDL_PollEvent(&ev))
            this->onEvent(&ev);

        this->onRender();
        this->onLoop();
    }
    this->onQuit();
    return 0;
}

std::string ClientClass::GetTime()
{
#ifdef _CLIENT_DEBUG_
    std::cout << "std::string ClientClass::GetTime()\n";
#endif // _SERVER_DEBUG_

    SYSTEMTIME t;
    GetLocalTime(&t);
    auto time = (t.wDay < 10 ? "0" : "") + std::to_string(t.wDay) + ".";
    time += (t.wMonth < 10 ? "0" : "") + std::to_string(t.wMonth) + ".";
    time += std::to_string(t.wYear) + " ";
    time += (t.wHour < 10 ? "0" : "") + std::to_string(t.wHour) + ":";
    time += (t.wMinute < 10 ? "0" : "") + std::to_string(t.wMinute) + ":";
    time += (t.wSecond < 10 ? "0" : "") + std::to_string(t.wSecond) + " ";
    return time;
}

void ClientClass::SendMsg()
{
#ifdef _CLIENT_DEBUG_
    std::cout << "void ClientClass::SendMsg()\n";
#endif // _SERVER_DEBUG_

    std::string r;
    if (this->sendMessage == "#")
    {
        this->msgHistory.push_back("Terminating connection");
        this->onExit();
        return;
    }
    r += this->GetTime() + "Client: " + this->sendMessage;

    char* buf = new char[512];
    ZeroMemory(buf, 512);
    CopyMemory(buf, r.c_str(), r.size());
    int result = send(this->ConnectSocket, buf, 512, 0);
    delete[] buf; buf = nullptr;

    if (result == SOCKET_ERROR)
    {
        this->msgHistory.push_back("ServerClass::onReturn() error");
        this->onExit();
        return;
    }
    this->sendMessage.clear();

    this->sending = false;
}
