#pragma once
#ifndef _CLIENT_CLASS_HPP_
#define _CLIENT_CLASS_HPP_

#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "Ws2_32.lib")

#include "ClassEvent.hpp"
#include "ClassSurface.hpp"
#include "Defines.hpp"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

class ClientClass : public ClassEvent
{
public:
	ClientClass();
	~ClientClass();

	int onExecute();

private:
	bool running;
	bool sending;
	std::string sendMessage;
	std::string recvMessage;
	std::string timeStamp;
	std::vector<std::string> msgHistory;
	std::ofstream fout;

	SDL_Window* window;
	SDL_Surface* windowSurf;
	SDL_Surface* background;
	SDL_Surface* icon;
	TTF_Font* font;

	WORD version;
	WSADATA wsaData;
	ADDRINFO hints;
	ADDRINFO* addrResult;
	SOCKET ConnectSocket;

	bool onInit(), InitWSA(), InitSDL();

	void onRender();
	void onLoop();

	void onQuit(), QuitWSA(), QuitSDL();

	void onEvent(SDL_Event* ev) override;
	void onExit() override;
	void onTextInput(char* text) override;
	void onReturn() override;
	void onBackspace() override;

	std::string GetTime();
	void SendMsg();

};

#endif
