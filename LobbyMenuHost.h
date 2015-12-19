#pragma once

#include <steamclientpublic.h>

class GameClient;
class MenuButton;
class Texture;
class Lobby;

class LobbyMenuHost
{
public:
	LobbyMenuHost(GameClient* game_client, Lobby* _lobby);
	~LobbyMenuHost();

	void runFrame();
	void setLobbySteamID(const CSteamID &steam_id_lobby);

private:
	void render();
	void input();
	void update();

	GameClient* _game_client;

	MenuButton* _menu_button1;
	MenuButton* _menu_button2;

	Texture* _texture_background;

	Lobby* _lobby;
};

