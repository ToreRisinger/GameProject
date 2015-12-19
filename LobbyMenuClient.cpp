#include "LobbyMenuClient.h"

#include "MenuButton.h"
#include "Texture.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Lobby.h"
#include <iostream>

LobbyMenuClient::LobbyMenuClient(GameClient* game_client, Lobby* lobby)
{
	_game_client = game_client;
	_lobby = lobby;

	_texture_background = _game_client->getResourceManager()->getTexture("texture_background_main_menu");

	_menu_button1 = new MenuButton(_game_client, (WINDOW_WIDTH / 2) - 100, 600, 200, 55, 38, "Back", "texture_menu_button", "texture_menu_button_highlighted");
}

LobbyMenuClient::~LobbyMenuClient()
{

}


void LobbyMenuClient::runFrame()
{
	render();
	update();
	input();
}

void LobbyMenuClient::render()
{
	_texture_background->render(0, 0);

	_menu_button1->render();
}

void LobbyMenuClient::input()
{
	_menu_button1->input();
	if (_menu_button1->isPressed())
		_game_client->changeGameClientState(BROWSE_SERVERS);

}

void LobbyMenuClient::update()
{
	_menu_button1->update();
}

//-----------------------------------------------------------------------------
// Purpose: Sets the ID of the lobby to display
//-----------------------------------------------------------------------------
void LobbyMenuClient::setLobbySteamID(const CSteamID &steam_id_lobby)
{
	_lobby->setLobbySteamID(steam_id_lobby);
}