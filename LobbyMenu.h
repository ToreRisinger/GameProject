#pragma once

#include <steamclientpublic.h>

class GameClient;
class MenuButton;
class Texture;
class Lobby;

class LobbyMenu
{
public:
	LobbyMenu(GameClient* game_client, Lobby* _lobby);
	~LobbyMenu();

	void runFrame();
	void setLobbySteamID(const CSteamID &steam_id_lobby);
	void setHost(bool value);
	bool isHost();

private:
	void render();
	void input();
	void update();

	bool _is_host;

	GameClient* _game_client;

	MenuButton* _menu_button1;
	MenuButton* _menu_button2;

	Texture* _texture_background;

	Lobby* _lobby;
};

