#pragma once

class GameClient;
class MenuButton;
class Texture;

class CreateGameMenu
{
public:
	CreateGameMenu(GameClient* game_client);
	~CreateGameMenu();

	void runFrame();

private:
	void render();
	void input();
	void update();

	GameClient* _game_client;

	MenuButton* _menu_button1;
	MenuButton* _menu_button2;

	Texture* _texture_background;
};

