#pragma once
#ifndef _CLASS_EVENT_HPP_
#define _CLASS_EVENT_HPP_

#include <SDL.h>
#include <SDL_ttf.h>

class ClassEvent
{
public:
    ClassEvent();
    virtual ~ClassEvent();
    virtual void onEvent(SDL_Event* ev);
    virtual void onExit() = 0;
    virtual void onTextInput(char* text) = 0;
    virtual void onKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode);
    virtual void onReturn() = 0;
    virtual void onBackspace() = 0;
};

#endif // !_CLASS_EVENT_HPP_
