#pragma once

#include "MenuButton.h"
#include "GameClient.h"
#include "Input.h"
#include "Keys.h"
#include "ResourceManager.h"

class LobbyBrowseButton : public MenuButton
{
public:
	LobbyBrowseButton(GameClient* game_client, int x, int y, int width, int height, int text_size, std::string text1, std::string text2, std::string text3, std::string button_texture, std::string button_texture_highlighted, std::string button_texture_selected)
		: MenuButton(game_client, x, y, width, height, text_size, text1, button_texture, button_texture_highlighted)
	{
		_texture_selected = _game_client->getResourceManager()->getTexture(button_texture_selected);

		_button_text2 = _game_client->getResourceManager()->getTextureText(text2, { 0xFF, 0xFF, 0xFF }, text_size);
		_button_text3 = _game_client->getResourceManager()->getTextureText(text3, { 0xFF, 0xFF, 0xFF }, text_size);
	}
	~LobbyBrowseButton();

	void input();
	void render();

	bool isSelected();
	void setSelect(bool value);

	
private:
	Texture* _texture_selected;

	Texture* _button_text2;
	Texture* _button_text3;

	bool _selected;

};

