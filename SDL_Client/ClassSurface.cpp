#include "ClassSurface.hpp"

ClassSurface::ClassSurface()
{
}

ClassSurface::~ClassSurface()
{
}

SDL_Surface* ClassSurface::loadSurface(const char* fileName, SDL_Surface* screen)
{
    SDL_Surface* temp = SDL_LoadBMP(fileName);
    if (!temp)
        nullptr;

    SDL_Surface* newSurf = SDL_ConvertSurface(temp, screen->format, 0);
    SDL_FreeSurface(temp);
    return newSurf;
}

TTF_Font* ClassSurface::loadFont(const char* fileName, int fontSize)
{
    TTF_Font* font = TTF_OpenFont(fileName, fontSize);
    return font;
}

void ClassSurface::drawSurface(SDL_Surface* srcSurface, SDL_Surface* dstSurface, int x, int y)
{
    if (!srcSurface || !dstSurface)
        return;

    SDL_Rect dstRect = { x, y };
    SDL_BlitSurface(srcSurface, nullptr, dstSurface, &dstRect);
}

void ClassSurface::drawFont(TTF_Font* font, SDL_Surface* dstSurface, const char* text, int x, int y)
{
    if (!font || !dstSurface || !text)
        return;

    SDL_Rect dstRect = { x, y };
    SDL_Color colour = { 255, 0, 0 };

    SDL_Surface* txtFont = TTF_RenderText_Solid(font, text, colour);
    SDL_BlitSurface(txtFont, nullptr, dstSurface, &dstRect);
    SDL_FreeSurface(txtFont);
}
