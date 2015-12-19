#include "Input.h"
#include "Keys.h"
#include <iostream>

Input::Input()
{
	for (int i = 0; i < NUM_KEYS; ++i)
	{
		_keysDown[i] = false;
		_keysPressed[i] = false;
	}

	_quit = false;

	_input_string = "";
	_input_string_max_size = 40;
}

Input::~Input()
{

}

void Input::takeInput()
{
	reset();

	_keysDown[MOUSE_WHEEL_UP] = false;
	_keysDown[MOUSE_WHEEL_DOWN] = false;

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN)
		{
			if (_keysDown[e.key.keysym.scancode] == false)
			{
				_keysPressed[e.key.keysym.scancode] = true;
			}

			_keysDown[e.key.keysym.scancode] = true;


			//Handle backspace
			if (e.key.keysym.sym == SDLK_BACKSPACE && _input_string.length() > 0)
			{
				//lop off character
				_input_string.pop_back();
			}
			//Handle copy
			else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
			{
				SDL_SetClipboardText(_input_string.c_str());
			}
			//Handle paste
			else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
			{
				_input_string += SDL_GetClipboardText();
				if (_input_string.length() > _input_string_max_size)
				{
					_input_string.erase(_input_string.begin() + _input_string_max_size, _input_string.end());
				}
			}
		}
		else if (e.type == SDL_TEXTINPUT)
		{
			//Not copy or pasting
			if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
			{
				//Append character
				if (_input_string.length() < _input_string_max_size)
				{
					_input_string += e.text.text;
				}
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			_keysDown[e.key.keysym.scancode] = false;
		}
		else if (e.type == SDL_MOUSEMOTION)
		{
			_mouseRelX = e.motion.xrel;
			_mouseRelY = e.motion.yrel;
			_mouseX = e.motion.x;
			_mouseY = e.motion.y;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (_keysDown[(int)e.button.button] == false)
			{
				_keysPressed[(int)e.button.button] = true;
			}

			_keysDown[(int)e.button.button] = true;
		}
		else if (e.type == SDL_MOUSEWHEEL) {
			if (e.wheel.y > 0) {
				_keysDown[MOUSE_WHEEL_UP] = true;
			}
			else if (e.wheel.y < 0) {
				_keysDown[MOUSE_WHEEL_DOWN] = true;
			}
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			_keysDown[(int)e.button.button] = false;
		}
		else if (e.type == SDL_QUIT)
		{
			_quit = true;
		}
			
	}
}

void Input::startStringInput(std::string startstring, int input_string_max_size)
{
	_input_string = startstring;
	_input_string_max_size = input_string_max_size;
}

std::string Input::getInputString()
{
	return _input_string;
}

void Input::reset()
{
	_mouseRelX = 0;
	_mouseRelY = 0;

	for (int i = 0; i < NUM_KEYS; ++i)
		_keysPressed[i] = false;
}

bool Input::getKeyDown(int key)
{
	return _keysDown[key];
}

bool Input::getKeyPressed(int key)
{
	return _keysPressed[key];
}

float Input::getMouseRelX()
{
	return _mouseRelX;
}

float Input::getMouseRelY()
{
	return _mouseRelY;
}

float Input::getMouseX()
{
	return _mouseX;
}

float Input::getMouseY()
{
	return _mouseY;
}

bool Input::getQuit()
{
	return _quit;
}