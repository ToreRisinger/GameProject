#include "MainMenu.h"

#include "GameClient.h"
#include "MenuButton.h"
#include "Texture.h"
#include "Game.h"
#include "ResourceManager.h"

MainMenu::MainMenu(GameClient* game_client)
{
	_game_client = game_client;

	_texture_background = _game_client->getResourceManager()->getTexture("texture_background_main_menu");

	_menu_button1 = new MenuButton(_game_client, (WINDOW_WIDTH / 2) - 100, 200, 200, 55, 38, "Solo", "texture_menu_button", "texture_menu_button_highlighted");
	_menu_button2 = new MenuButton(_game_client, (WINDOW_WIDTH / 2) - 100, 300, 200, 55, 38, "Join", "texture_menu_button", "texture_menu_button_highlighted");
	_menu_button3 = new MenuButton(_game_client, (WINDOW_WIDTH / 2) - 100, 400, 200, 55, 38, "Host", "texture_menu_button", "texture_menu_button_highlighted");
	_menu_button4 = new MenuButton(_game_client, (WINDOW_WIDTH / 2) - 100, 500, 200, 55, 38, "Library", "texture_menu_button", "texture_menu_button_highlighted");
	_menu_button5 = new MenuButton(_game_client, (WINDOW_WIDTH / 2) - 100, 600, 200, 55, 38, "Exit", "texture_menu_button", "texture_menu_button_highlighted");
}

MainMenu::~MainMenu()
{
}

void MainMenu::runFrame()
{
	render();
	update();
	input();
}

void MainMenu::render()
{
	_texture_background->render(0, 0);

	_menu_button1->render();
	_menu_button2->render();
	_menu_button3->render();
	_menu_button4->render();
	_menu_button5->render();
}

void MainMenu::input()
{
	_menu_button1->input();
	if (_menu_button1->isPressed())
		_game_client->changeGameClientState(MAIN_MENU);

	_menu_button2->input();
	if (_menu_button2->isPressed())
		_game_client->changeGameClientState(BROWSE_SERVERS);

	_menu_button3->input();
	if (_menu_button3->isPressed())
		_game_client->changeGameClientState(CREATING_GAME);

	_menu_button4->input();
	if (_menu_button4->isPressed())
		_game_client->changeGameClientState(MAIN_MENU);

	_menu_button5->input();
	if (_menu_button5->isPressed())
		_game_client->changeGameClientState(QUIT);
}

void MainMenu::update()
{
	_menu_button1->update();
	_menu_button2->update();
	_menu_button3->update();
	_menu_button4->update();
	_menu_button5->update();
}
