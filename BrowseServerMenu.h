#pragma once

#include <vector>
#include <steam_api.h>
#include "Timer.h"

class GameClient;
class MenuButton;
class Texture;
class LobbyBrowser;

// An lobby list item
struct Lobby_t
{
	CSteamID steam_id_lobby;
	std::string lobby_name = "";
	std::string host_name = "";
	std::string map_name = "";
	int max_nr_of_players = -1;
	int nr_of_players = -1;
};

class BrowseServerMenu
{
public:
	BrowseServerMenu(GameClient* game_client);
	~BrowseServerMenu();

	// Request the lobby list
	void refresh();

	void runFrame();

private:

	void render();
	void input();
	void update();

	void removeInvalidLobby();

	GameClient* _game_client;

	MenuButton* _menu_button1;
	MenuButton* _menu_button2;
	MenuButton* _menu_button3;

	Texture* _texture_background;

	std::vector<Lobby_t>  _lobby_list;

	LobbyBrowser* _lobby_browser;

	Timer _refresh_timer;
	bool _refreshing_lobby_list;

	CCallResult<BrowseServerMenu, LobbyMatchList_t> _steam_call_result_lobby_match_list;
	void OnLobbyMatchListCallback(LobbyMatchList_t *pLobbyMatchList, bool bIOFailure);
	STEAM_CALLBACK(BrowseServerMenu, OnLobbyDataUpdatedCallback, LobbyDataUpdate_t);

};

