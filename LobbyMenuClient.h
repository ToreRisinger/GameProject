#pragma once

#include <steamclientpublic.h>
#include <steam_api.h>

class GameClient;
class MenuButton;
class Texture;
class Lobby;

class LobbyMenuClient
{
public:
	LobbyMenuClient(GameClient* game_client, Lobby* lobby);
	~LobbyMenuClient();

	void runFrame();
	void setLobbySteamID(const CSteamID &steam_id_lobby);

private:
	void render();
	void input();
	void update();

	GameClient* _game_client;

	MenuButton* _menu_button1;

	Texture* _texture_background;

	Lobby* _lobby;
};

