#include "CreateGameMenu.h"

#include "MenuButton.h"
#include "Texture.h"
#include "Game.h"
#include "ResourceManager.h"

CreateGameMenu::CreateGameMenu(GameClient* game_client)
{
	_game_client = game_client;

	_texture_background = _game_client->getResourceManager()->getTexture("texture_background_main_menu");

	_menu_button1 = new MenuButton(_game_client, (WINDOW_WIDTH / 2) - 100, 500, 200, 55, 38, "Confirm", "texture_menu_button", "texture_menu_button_highlighted");
	_menu_button2 = new MenuButton(_game_client, (WINDOW_WIDTH / 2) - 100, 600, 200, 55, 38, "Back", "texture_menu_button", "texture_menu_button_highlighted");
}


CreateGameMenu::~CreateGameMenu()
{

}

void CreateGameMenu::runFrame()
{
	render();
	update();
	input();
}

void CreateGameMenu::render()
{
	_texture_background->render(0, 0);

	_menu_button1->render();
	_menu_button2->render();
}

void CreateGameMenu::input()
{
	_menu_button1->input();
	if (_menu_button1->isPressed())
		_game_client->changeGameClientState(CREATING_LOBBY);

	_menu_button2->input();
	if (_menu_button2->isPressed())
		_game_client->changeGameClientState(MAIN_MENU);
}

void CreateGameMenu::update()
{
	_menu_button1->update();
	_menu_button2->update();
}

