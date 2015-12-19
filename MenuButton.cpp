#include "MenuButton.h"

#include "Game.h"
#include "Keys.h"
#include <iostream>
#include "Texture.h"
#include "GameClient.h"
#include "ResourceManager.h"
#include "Input.h"

MenuButton::MenuButton(GameClient* game_client, int x, int y, int width, int height, int text_size, std::string button_name, std::string button_texture, std::string button_texture_highlighted)
{
	_game_client = game_client;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_button_down = false;

	_is_pressed = false;

	_button_texture = _game_client->getResourceManager()->getTexture(button_texture);
	_button_texture_hightlighted = _game_client->getResourceManager()->getTexture(button_texture_highlighted);
	_active_texture = _button_texture;

	_button_text1 = _game_client->getResourceManager()->getTextureText(button_name, { 0xFF, 0xFF, 0xFF }, text_size);
}


MenuButton::~MenuButton()
{
	delete _button_text1;
}

void MenuButton::render()
{
	_active_texture->render(_x, _y, _width, _height);

	int middle_x = _x + _width / 2;
	int middle_y = _y + _height / 2;

	_button_text1->render(middle_x - _button_text1->getWidth() / 2, middle_y - _button_text1->getHeight() / 2.3);
}

void MenuButton::input()
{
	_is_pressed = false;
	if (_game_client->getInput()->getMouseX() >= _x && _game_client->getInput()->getMouseX() <= _x + _width &&
		_game_client->getInput()->getMouseY() >= _y && _game_client->getInput()->getMouseY() <= _y + _height) {

		_active_texture = _button_texture_hightlighted;

		if (_game_client->getInput()->getKeyPressed(MOUSE_LEFT_BUTTON))
		{
			_is_pressed = true;
		}
					
	}
	else
	{
		_active_texture = _button_texture;
	}
}

void MenuButton::update()
{

}

bool MenuButton::isPressed()
{
	return _is_pressed;
}

void MenuButton::setX(int x)
{
	_x = x;
}

void MenuButton::setY(int y)
{
	_y = y;
}