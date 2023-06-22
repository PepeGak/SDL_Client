#include "ClientClass.hpp"


//В строке YYYY:MM:DD HH:MM:SS Client: [28]text
void ClientClass::onRender()
{
#ifdef _CLIENT_DEBUG_
    std::cout << "void ClientClass::onRender()\n";
#endif // _SERVER_DEBUG_
    
    ClassSurface::drawSurface(this->background, this->windowSurf, 0, 0);

    if (this->msgHistory.size() >= 31)
        while (this->msgHistory.size() != 30)
            this->msgHistory.erase(this->msgHistory.begin());

    for (int index = 0, lin = 0; index < this->msgHistory.size(); index++)
    {
        std::string line(this->msgHistory[index]);

        for (int total = line.length(), part = 0; part <= total / MAX_LEN_STR; total++, part++)
        {
            ClassSurface::drawFont(this->font, this->windowSurf, line.substr(0, MAX_LEN_STR - 1).c_str(), 5, 10 + 20 * lin++);
            line.erase(0, MAX_LEN_STR - 1);
        }

    }

    SDL_UpdateWindowSurface(this->window);
}