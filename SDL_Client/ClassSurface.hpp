#pragma once
#ifndef _CLASS_SURFACE_HPP_
#define _CLASS_SURFACE_HPP_

#include <SDL.h>
#include <SDL_ttf.h>

class ClassSurface
{
public:
    ClassSurface();
    ~ClassSurface();
    static SDL_Surface* loadSurface(const char* fileName,
        SDL_Surface* screen);
    static TTF_Font* loadFont(const char* fileName,
        int fontSize);
    static void drawSurface(SDL_Surface* srcSurface,
        SDL_Surface* dstSurface, int x, int y);
    static void drawFont(TTF_Font* font, SDL_Surface* dstSurface,
        const char* text, int x, int y);
};

#endif
