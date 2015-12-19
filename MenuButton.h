#pragma once

#include <string>
#include "GameClient.h"

class Texture;

class MenuButton
{
public:
	MenuButton(GameClient* game_client, int x, int y, int width, int height, int text_size, std::string button_name, std::string button_texture, std::string button_texture_highlighted);
	~MenuButton();

	void render();
	void input();
	void update();

	void setX(int x);
	void setY(int y);

	bool isPressed();

protected:
	GameClient* _game_client;

	Texture* _button_text1;

	Texture* _active_texture;
	Texture* _button_texture;
	Texture* _button_texture_hightlighted;

	GameClientState _game_state;

	bool _is_pressed;

	int _x;
	int _y;
	int _width;
	int _height;

	bool _button_down;
};

