#include "ClassEvent.hpp"

ClassEvent::ClassEvent() { }

ClassEvent::~ClassEvent() { }

void ClassEvent::onEvent(SDL_Event* ev)
{
	switch (ev->type)
	{
	case SDL_QUIT:
		this->onExit();
		break;

	case SDL_KEYDOWN:
		this->onKeyDown(ev->key.keysym.sym, ev->key.keysym.mod, ev->key.keysym.scancode);
		break;

	case SDL_TEXTINPUT:
		this->onTextInput(ev->text.text);
		break;

	default:
		break;
	}
}

void ClassEvent::onKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode)
{
	switch (sym)
	{
	case SDLK_ESCAPE:
		this->onExit();
		break;

	case SDLK_RETURN:
		this->onReturn();
		break;

	case SDLK_BACKSPACE:
		this->onBackspace();
		break;
	}
}
