#pragma once

#include "BrowseServerMenu.h"

class GameClient;
class Texture;
class MenuButton;
class LobbyBrowseButton;

class LobbyBrowser
{
public:
	LobbyBrowser(GameClient* game_client);
	~LobbyBrowser();

	void runFrame();
	void setLobbyList(std::vector<Lobby_t> lobby_list);
	void clearLobbyList();

	void joinLobby();

private:
	void render();
	void input();
	void update();

	void toupper(std::string &s);
	bool strcasecmp(std::string lhs, std::string rhs);
	void swap(std::pair<Lobby_t, LobbyBrowseButton*> & lhs, std::pair<Lobby_t, LobbyBrowseButton*> & rhs);

	GameClient* _game_client;

	Texture* _texture_background;

	MenuButton* _game_name_button;
	MenuButton* _host_name_button;
	MenuButton* _map_name_button;
	MenuButton* _nr_of_players_button;

	bool _pressed1;
	bool _pressed2;
	bool _pressed3;
	bool _pressed4;

	std::vector<std::pair<Lobby_t, LobbyBrowseButton*>>_lobby_list;

	int _y;
	int _x;

	int _first_element_in_list;

	
};

