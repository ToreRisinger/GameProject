#include "LobbyBrowseButton.h"

#include "Texture.h"

LobbyBrowseButton::~LobbyBrowseButton()
{
	_selected = false;
	if (_button_text1) 
	{
		delete _button_text1;
		_button_text1 = nullptr;
	}
	
	if (_button_text2)
	{
		delete _button_text2;
		_button_text2 = nullptr;
	}
		
	if (_button_text3)
	{
		delete _button_text3;
		_button_text3 = nullptr;
	}

	if (_button_text4)
	{
		delete _button_text4;
		_button_text4 = nullptr;
	}
}

void LobbyBrowseButton::render()
{
	_active_texture->render(_x, _y, _width, _height);

	int middle_y = _y + _height / 2;

	_button_text1->render(_x + (901 / 8) - _button_text1->getWidth() / 2, middle_y - _button_text1->getHeight() / 2.3);
	_button_text2->render(_x + (901 / 8) + (901 / 4) - _button_text2->getWidth() / 2, middle_y - _button_text2->getHeight() / 2.3);
	_button_text3->render(_x + (901 / 8) + (901 / 4) * 2 - _button_text3->getWidth() / 2, middle_y - _button_text3->getHeight() / 2.3);
	_button_text4->render(_x + (901 / 8) + (901 / 4) * 3 - _button_text4->getWidth() / 2, middle_y - _button_text4->getHeight() / 2.3);
}


void LobbyBrowseButton::input()
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
	

	if (_selected)
	{
		_active_texture = _texture_selected;
	}
	
}

void LobbyBrowseButton::setSelect(bool value)
{
	_selected = value;
}

bool LobbyBrowseButton::isSelected()
{
	return _selected;
}