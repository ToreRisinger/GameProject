#include "BrowseServerMenu.h"

#include "MenuButton.h"
#include "Game.h"
#include "GameClient.h"
#include "ResourceManager.h"
#include "LobbyBrowser.h"

#include <iomanip>
#include <iostream>

BrowseServerMenu::BrowseServerMenu(GameClient* game_client)
{
	_game_client = game_client;

	_refreshing_lobby_list = false;

	_lobby_browser = new LobbyBrowser(_game_client);

	_texture_background = _game_client->getResourceManager()->getTexture("texture_background_main_menu");

	_menu_button1 = new MenuButton(_game_client, (WINDOW_WIDTH / 2) + 353, 85, 100, 27, 38 / 2, "Refresh", "texture_menu_button", "texture_menu_button_highlighted");
	_menu_button2 = new MenuButton(_game_client, (WINDOW_WIDTH / 2) - 100, 500, 200, 55, 38, "Join", "texture_menu_button", "texture_menu_button_highlighted");
	_menu_button3 = new MenuButton(_game_client, (WINDOW_WIDTH / 2) - 100, 600, 200, 55, 38, "Back", "texture_menu_button", "texture_menu_button_highlighted");
}

BrowseServerMenu::~BrowseServerMenu()
{

}

void BrowseServerMenu::runFrame()
{
	render();
	update();
	input();

	_lobby_browser->runFrame();
}

void BrowseServerMenu::render()
{
	_texture_background->render(0, 0);

	_menu_button1->render();
	_menu_button2->render();
	_menu_button3->render();
}

void BrowseServerMenu::input()
{
	_menu_button1->input();
	if (_menu_button1->isPressed())
	{
		_refreshing_lobby_list = false;
		_refresh_timer.start();
		_lobby_browser->clearLobbyList();
		refresh();	
	}
		
	_menu_button2->input();
	if (_menu_button2->isPressed())
	{
		_lobby_browser->joinLobby();
	}
		
	_menu_button3->input();
	if (_menu_button3->isPressed())
	{
		_game_client->changeGameClientState(MAIN_MENU);
	}
		
}

void BrowseServerMenu::update()
{
	if (_refreshing_lobby_list && _refresh_timer.getElapsedTime() > 3000)
	{
		_refreshing_lobby_list = false;
		removeInvalidLobby();
		_lobby_browser->setLobbyList(_lobby_list);
	}
}

//-----------------------------------------------------------------------------
// Purpose: Print all the lobby items that are in the lobby list
//-----------------------------------------------------------------------------
void BrowseServerMenu::removeInvalidLobby()
{
	std::vector<Lobby_t> new_lobby_list;
	for (int i = 0; i < _lobby_list.size(); i++)
	{
		if (_lobby_list.at(i).host_name != "" &&
			_lobby_list.at(i).lobby_name != "" &&
			_lobby_list.at(i).map_name != "" &&
			_lobby_list.at(i).max_nr_of_players != -1 && 
			_lobby_list.at(i).nr_of_players != -1) 
		{
			new_lobby_list.push_back(_lobby_list.at(i));
		}
	}

	_lobby_list = new_lobby_list;
}


//-----------------------------------------------------------------------------
// Purpose: Request the lobby list
//-----------------------------------------------------------------------------
void BrowseServerMenu::refresh()
{
	if (!_refreshing_lobby_list)
	{
		_refreshing_lobby_list = true;

		// request all lobbies for this game
		SteamAPICall_t hSteamAPICall = SteamMatchmaking()->RequestLobbyList();
		// set the function to call when this API call has completed
		_steam_call_result_lobby_match_list.Set(hSteamAPICall, this, &BrowseServerMenu::OnLobbyMatchListCallback);
	}
}

//-----------------------------------------------------------------------------
// Purpose: Callback, on a list of lobbies being received from the Steam back-end
//-----------------------------------------------------------------------------
void BrowseServerMenu::OnLobbyMatchListCallback(LobbyMatchList_t *pCallback, bool bIOFailure)
{

	_lobby_list.clear();

	if (bIOFailure)
	{
		// we had a Steam I/O failure - we probably timed out talking to the Steam back-end servers
		// doesn't matter in this case, we can just act if no lobbies were received
	}

	// lobbies are returned in order of closeness to the user, so add them to the list in that order
	for (uint32 iLobby = 0; iLobby < pCallback->m_nLobbiesMatching; iLobby++)
	{
		
		CSteamID steam_id_lobby = SteamMatchmaking()->GetLobbyByIndex(iLobby);

		Lobby_t lobby;
		lobby.steam_id_lobby = steam_id_lobby;

		_lobby_list.push_back(lobby);

		// we don't have info about the lobby yet, request it
		// results will be returned via LobbyDataUpdate_t callback
		SteamMatchmaking()->RequestLobbyData(steam_id_lobby);
	}
}


//-----------------------------------------------------------------------------
// Purpose: Callback, on a list of lobbies being received from the Steam back-end
//-----------------------------------------------------------------------------
void BrowseServerMenu::OnLobbyDataUpdatedCallback(LobbyDataUpdate_t *pCallback)
{	
	for (int i = 0; i < _lobby_list.size(); i++)
	{
		if (_lobby_list.at(i).steam_id_lobby == pCallback->m_ulSteamIDLobby)
		{
			// pull the name from the lobby metadata
			_lobby_list.at(i).lobby_name = SteamMatchmaking()->GetLobbyData(_lobby_list.at(i).steam_id_lobby, "lobby_name");
			_lobby_list.at(i).host_name = SteamMatchmaking()->GetLobbyData(_lobby_list.at(i).steam_id_lobby, "host_name");
			_lobby_list.at(i).map_name = SteamMatchmaking()->GetLobbyData(_lobby_list.at(i).steam_id_lobby, "map_name");
			_lobby_list.at(i).max_nr_of_players = std::stoi(SteamMatchmaking()->GetLobbyData(_lobby_list.at(i).steam_id_lobby, "max_nr_of_players"));
			_lobby_list.at(i).nr_of_players = std::stoi(SteamMatchmaking()->GetLobbyData(_lobby_list.at(i).steam_id_lobby, "nr_of_players"));
			//_lobby_list.at(i).nr_of_players = SteamMatchmaking()->GetNumLobbyMembers(_lobby_list.at(i).steam_id_lobby);
		}
	}
}
