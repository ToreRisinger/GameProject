#pragma once

#include <steamclientpublic.h>

class GameClient;
class MenuButton;
class Texture;


class LobbyMenuHost
{
public:
	LobbyMenuHost(GameClient* game_client);
	~LobbyMenuHost();

	void runFrame();
	void SetLobbySteamID(const CSteamID &steam_id_lobby);

private:
	void render();
	void input();
	void update();

	GameClient* _game_client;

	MenuButton* _menu_button1;
	MenuButton* _menu_button2;

	Texture* _texture_background;

	CSteamID _steam_id_lobby;
};

