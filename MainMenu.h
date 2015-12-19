#pragma once

class Texture;
class MenuButton;
class GameClient;

class MainMenu
{
public:
	MainMenu(GameClient* game_client);
	~MainMenu();

	void runFrame();

private:
	void render();
	void input();
	void update();

	GameClient* _game_client;

	MenuButton* _menu_button1;
	MenuButton* _menu_button2;
	MenuButton* _menu_button3;
	MenuButton* _menu_button4;
	MenuButton* _menu_button5;

	Texture* _texture_background;

};

