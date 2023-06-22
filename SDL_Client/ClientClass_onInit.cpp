#include "ClientClass.hpp"

bool ClientClass::onInit()
{
#ifdef _CLIENT_DEBUG_
    std::cout << "bool ClientClass::onInit()\n";
#endif // _SERVER_DEBUG_
    
    this->fout.open("History.txt");
    if (!this->fout.is_open())
        return false;
    if (!this->InitSDL())
        return false;
    if (!this->InitWSA())
        return false;
    return true;
}

bool ClientClass::InitSDL()
{
#ifdef _CLIENT_DEBUG_
    std::cout << "bool ClientClass::InitSDL()\n";
#endif // _SERVER_DEBUG_

    if (SDL_Init(SDL_INIT_EVERYTHING))
        return false;
    if (TTF_Init())
        return false;

    this->window = SDL_CreateWindow(WINDOW_NAME,
        10, 60,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!this->window)
        return false;

    this->windowSurf = SDL_GetWindowSurface(this->window);
    if (!this->windowSurf)
        return false;

    this->background = ClassSurface::loadSurface("Assets/Background.bmp", this->windowSurf);
    if (!this->background)
        return false;

    this->icon = ClassSurface::loadSurface("Assets/Icon.bmp", this->windowSurf);
    if (!this->icon)
        return false;
    SDL_SetWindowIcon(this->window, this->icon);

    this->font = ClassSurface::loadFont("Assets/Font.ttf", 24);
    if (!this->font)
        return false;

    return true;
}

bool ClientClass::InitWSA()
{
#ifdef _CLIENT_DEBUG_
    std::cout << "bool ClientClass::InitWSA()\n";
#endif // _SERVER_DEBUG_

    if (WSAStartup(this->version, &this->wsaData))
        return false;

    if (getaddrinfo("localhost", "666", &this->hints, &this->addrResult))
        return false;

    this->ConnectSocket = socket(this->addrResult->ai_family,
        this->addrResult->ai_socktype, this->addrResult->ai_protocol);
    if (this->ConnectSocket == INVALID_SOCKET)
        return false;

    if (connect(this->ConnectSocket, 
        this->addrResult->ai_addr, 
        this->addrResult->ai_addrlen) == SOCKET_ERROR)
        return false;

    return true;
}


