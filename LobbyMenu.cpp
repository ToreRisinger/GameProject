#include "LobbyMenu.h"

#include "MenuButton.h"
#include "Texture.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Lobby.h"

LobbyMenu::LobbyMenu(GameClient* game_client, Lobby* lobby)
{
	_game_client = game_client;
	_lobby = lobby;

	_is_host = false;

	_texture_background = _game_client->getResourceManager()->getTexture("texture_background_main_menu");

	_menu_button1 = new MenuButton(_game_client, (WINDOW_WIDTH / 2) - 100, 500, 200, 55, 38, "Start", "texture_menu_button", "texture_menu_button_highlighted");
	_menu_button2 = new MenuButton(_game_client, (WINDOW_WIDTH / 2) - 100, 600, 200, 55, 38, "Back", "texture_menu_button", "texture_menu_button_highlighted");
}


LobbyMenu::~LobbyMenu()
{

}

void LobbyMenu::runFrame()
{
	render();
	update();
	input();

	_lobby->runFrame();
}

void LobbyMenu::render()
{
	_texture_background->render(0, 0);

	if (_is_host)
		_menu_button1->render();
	
	_menu_button2->render();
}

void LobbyMenu::input()
{

	if (_is_host)
	{
		_menu_button1->input();
		if (_menu_button1->isPressed())
			_game_client->changeGameClientState(HOST_IN_LOBBY);
	}

	_menu_button2->input();
	if (_menu_button2->isPressed())
		_game_client->changeGameClientState(MAIN_MENU);
}

void LobbyMenu::update()
{
	if (_is_host)
		_menu_button1->update();

	_menu_button2->update();

	if (_lobby->isHost())
	{
		_is_host = true;
	}
}

//-----------------------------------------------------------------------------
// Purpose: Sets the ID of the lobby to display
//-----------------------------------------------------------------------------
void LobbyMenu::setLobbySteamID(const CSteamID &steam_id_lobby)
{
	_lobby->setLobbySteamID(steam_id_lobby);
}

void LobbyMenu::setHost(bool value)
{
	_is_host = value;
}

bool LobbyMenu::isHost()
{
	return _is_host;
}

