#include "ClientClass.hpp"

void ClientClass::onQuit()
{
    this->fout.close();
    this->QuitWSA();
    this->QuitSDL();
}

void ClientClass::QuitWSA()
{
    if (this->ConnectSocket != INVALID_SOCKET)
        shutdown(this->ConnectSocket, SD_BOTH);

    if (this->ConnectSocket != INVALID_SOCKET)
        closesocket(this->ConnectSocket);
    this->ConnectSocket = INVALID_SOCKET;

    if (this->addrResult)
        freeaddrinfo(this->addrResult);
    this->addrResult = nullptr;

    WSACleanup();
}

void ClientClass::QuitSDL()
{
    SDL_FreeSurface(this->background);
    this->background = nullptr;

    SDL_FreeSurface(this->windowSurf);
    this->windowSurf = nullptr;

    if (this->font)
        TTF_CloseFont(this->font);
    this->font = nullptr;

    if (this->window)
        SDL_DestroyWindow(this->window);
    this->window = nullptr;

    TTF_Quit();
    SDL_Quit();
}
