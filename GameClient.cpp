#include "GameClient.h"

#include "MainMenu.h"
#include "Input.h"
#include "Game.h"
#include "Input.h"
#include "ResourceManager.h"
#include "CreateGameMenu.h"
#include "LobbyMenu.h"
#include "BrowseServerMenu.h"
#include "GameServer.h"
#include "Lobby.h"

#include <random>

#include <iostream>

#include "steam_api.h"
#include "steam_gameserver.h"

GameClient::GameClient(Game* game)
{
	_game = game;

	_input = _game->input;

	_resource_manager = _game->resource_manager;

	_renderer = _game->renderer;

	_game_client_state = MAIN_MENU;

	_main_menu = new MainMenu(this);
	_create_game_menu = new CreateGameMenu(this);

	_lobby = new Lobby(this);
	
	_lobby_menu = new LobbyMenu(this, _lobby);
	_browse_server_menu = new BrowseServerMenu(this);

	_game_server = nullptr;

	_steam_user_stats = SteamUserStats();

	_steam_id_this_user = SteamUser()->GetSteamID();
}

GameClient::~GameClient()
{

}

void GameClient::runFrame()
{
	// Run Steam client callbacks
	SteamAPI_RunCallbacks();

	bool success = _steam_user_stats->RequestCurrentStats();

	if (_game_client_state == MAIN_MENU)
	{
		_main_menu->runFrame();
	}
	else if (_game_client_state == CREATING_GAME)
	{
		_create_game_menu->runFrame();
	}
	else if (_game_client_state == BROWSE_SERVERS)
	{
		_browse_server_menu->runFrame();
	}
	else if (_game_client_state == CREATING_LOBBY)
	{
		// draw some text about creating lobby (may take a second or two)
	}
	else if (_game_client_state == HOST_IN_LOBBY)
	{	
		_lobby_menu->runFrame();
	}
	else if (_game_client_state == CLIENT_IN_LOBBY)
	{
		_lobby_menu->runFrame();
	}

	if (_input->getQuit())
	{
		changeGameClientState(QUIT);
	}

	// If we've started a local server run it
	if (_game_server)
	{
		_game_server->runFrame();
	}
}

void GameClient::changeGameClientState(GameClientState game_client_state)
{
	// LEAVING A STATE
	if (_game_client_state == HOST_IN_LOBBY && game_client_state != HOST_IN_LOBBY)
	{
		// leave the lobby
		SteamMatchmaking()->LeaveLobby(_steam_id_lobby);
		_steam_id_lobby = CSteamID();
		_lobby_menu->setLobbySteamID(_steam_id_lobby);
	}
	else if (_game_client_state == CLIENT_IN_LOBBY && game_client_state != CLIENT_IN_LOBBY)
	{
		// leave the lobby
		SteamMatchmaking()->LeaveLobby(_steam_id_lobby);
		_steam_id_lobby = CSteamID();
		_lobby_menu->setLobbySteamID(_steam_id_lobby);
	}

	// ENTERING A STATE
	if (game_client_state == QUIT && _game_client_state != QUIT)
	{
		_game_client_state = QUIT;
		_quit = true;
	}
	else if (game_client_state == MAIN_MENU && _game_client_state != MAIN_MENU)
	{
		_game_client_state = MAIN_MENU;

	}
	else if (game_client_state == LIBRARY && _game_client_state != LIBRARY)
	{
		_game_client_state = LIBRARY;
	}
	else if (game_client_state == BROWSE_SERVERS && _game_client_state != BROWSE_SERVERS)
	{
		_game_client_state = BROWSE_SERVERS;
	}
	else if (game_client_state == JOINING_LOBBY && _game_client_state != JOINING_LOBBY)
	{
		_game_client_state = JOINING_LOBBY;
	}
	else if (game_client_state == CREATING_GAME && _game_client_state != CREATING_GAME)
	{
		_game_client_state = CREATING_GAME;
	}
	else if (game_client_state == CREATING_LOBBY && _game_client_state != CREATING_LOBBY)
	{
		_game_client_state = CREATING_LOBBY;

		//Create the lobby
		if (!_steam_call_result_lobby_created.IsActive())
		{
			//Create lobby
			SteamAPICall_t hSteamAPICall = SteamMatchmaking()->CreateLobby(k_ELobbyTypePublic /* public lobby, anyone can find it */, 4);

			//Set what function should be called when this is completed
			_steam_call_result_lobby_created.Set(hSteamAPICall, this, &GameClient::OnLobbyCreated);
		}
		SteamFriends()->SetRichPresence("status", "Creating a lobby");		
	}
	else if (game_client_state == HOST_IN_LOBBY && _game_client_state != HOST_IN_LOBBY)
	{
		_game_client_state = HOST_IN_LOBBY;
	}
	else if (game_client_state == CLIENT_IN_LOBBY && _game_client_state != CLIENT_IN_LOBBY)
	{
		_game_client_state = CLIENT_IN_LOBBY;
	}
	else if (game_client_state == INGAME && _game_client_state != INGAME)
	{
		_game_client_state = INGAME;
	}
}

void GameClient::joinLobby(CSteamID steam_id_lobby)
{
	SteamAPICall_t hSteamAPICall = SteamMatchmaking()->JoinLobby(steam_id_lobby);

	//Set what function should be called when this is completed
	_steam_call_result_lobby_entered.Set(hSteamAPICall, this, &GameClient::OnLobbyEntered);
}

//-----------------------------------------------------------------------------
// Purpose: Finishes up entering a lobby of our own creation
//-----------------------------------------------------------------------------
void GameClient::OnLobbyCreated(LobbyCreated_t *pCallback, bool bIOFailure)
{
	if (_game_client_state != CREATING_LOBBY)
		return;

	// record which lobby we're in
	if (pCallback->m_eResult == k_EResultOK)
	{
		// success
		_steam_id_lobby = pCallback->m_ulSteamIDLobby;
		_lobby_menu->setLobbySteamID(_steam_id_lobby);
	
		// set the name of the lobby if it's ours

		std::string lobby_name;
		std::string map_name;

		std::random_device rd;

		int rnd = rd() % 9999999;

		//std::cout << "-----CREATE LOBBY-----" << std::endl;
		//std::cout << "Enter lobby name: " << std::endl;
		//std::cin >> lobby_name;

		//std::cout << "Enter map name: " << std::endl;
		//std::cin >> map_name;

		std::string host_name = SteamFriends()->GetPersonaName();

		std::cout << "DEBUG: Creating lobby with name: " << SteamFriends()->GetPersonaName() << std::endl;

		//SteamMatchmaking()->SetLobbyData(_steam_id_lobby, "lobby_name", lobby_name.c_str());
		//SteamMatchmaking()->SetLobbyData(_steam_id_lobby, "map_name", map_name.c_str());

		SteamMatchmaking()->SetLobbyData(_steam_id_lobby, "lobby_name", std::to_string(rnd).c_str());
		SteamMatchmaking()->SetLobbyData(_steam_id_lobby, "map_name", std::to_string(rnd).c_str());
		
		SteamMatchmaking()->SetLobbyData(_steam_id_lobby, "host_name", host_name.c_str());
		SteamMatchmaking()->SetLobbyData(_steam_id_lobby, "max_nr_of_players", std::to_string(4).c_str());
		int nr_of_players = SteamMatchmaking()->GetNumLobbyMembers(_steam_id_lobby);
		SteamMatchmaking()->SetLobbyData(_steam_id_lobby, "nr_of_players", std::to_string(nr_of_players).c_str());

		// mark that we're in the lobby
		changeGameClientState(HOST_IN_LOBBY);
		_lobby_menu->setHost(true);
	}
	else
	{
		// failed, show error
		std::cout << "ERROR in OnLobbyCreated(): Failed to create lobby (lost connection to Steam back-end servers." << std::endl;
		changeGameClientState(MAIN_MENU);
	}
}

//-----------------------------------------------------------------------------
// Purpose: Finishes up entering a lobby
//-----------------------------------------------------------------------------
void GameClient::OnLobbyEntered(LobbyEnter_t *pCallback, bool bIOFailure)
{
	if (_game_client_state != JOINING_LOBBY)
			return;

	if (pCallback->m_EChatRoomEnterResponse != k_EChatRoomEnterResponseSuccess)
	{
		// failed, show error
		std::cout << "Failed to enter lobby" << std::endl;;
		changeGameClientState(BROWSE_SERVERS);
		return;
	}

	// success

	// move forward the state
	_steam_id_lobby = pCallback->m_ulSteamIDLobby;
	_lobby_menu->setLobbySteamID(_steam_id_lobby);

	int nr_of_players = SteamMatchmaking()->GetNumLobbyMembers(_steam_id_lobby);

	changeGameClientState(CLIENT_IN_LOBBY);
	_lobby_menu->setHost(false);
}

bool GameClient::isQuit()
{
	return _quit;
}

SDL_Renderer* GameClient::getRenderer()
{
	return _renderer;
}

Input* GameClient::getInput()
{
	return _input;
}

ResourceManager* GameClient::getResourceManager()
{
	return _resource_manager;
}

CSteamID GameClient::getThisUserSteamId()
{
	return _steam_id_this_user;
}