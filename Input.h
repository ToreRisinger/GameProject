#pragma once
#include <SDL.h>
#include <string>

class Input
{
public:
	static const int NUM_KEYS = 512;
	static const int NUM_MOUSEBUTTONS = 256;

	Input();
	~Input();

	void takeInput();
	void reset();

	bool getKeyDown(int key);
	bool getKeyPressed(int key);
	float getMouseRelX();
	float getMouseRelY();
	float getMouseX();
	float getMouseY();
	bool getQuit();

	void startStringInput(std::string start_string, int input_string_max_size);

	std::string getInputString();

private:
	bool _keysDown[NUM_KEYS];
	bool _keysPressed[NUM_KEYS];

	float _mouseRelX;
	float _mouseRelY;
	float _mouseX;
	float _mouseY;

	std::string _input_string;
	int _input_string_max_size;

	bool _quit;
};