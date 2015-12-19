#pragma once

#include <steamclientpublic.h>
#include <isteammatchmaking.h>
#include <steam_api.h>
#include "Timer.h"

class MainMenu;
class Input;
class Game;
class ResourceManager;
class CreateGameMenu;
class LobbyMenu;
class GameServer;
class BrowseServerMenu;
class Lobby;
struct SDL_Renderer;

enum GameClientState {
	QUIT, 
	MAIN_MENU, 
	LIBRARY, 
	BROWSE_SERVERS, 
	JOINING_LOBBY,
	CREATING_GAME, 
	CREATING_LOBBY, 
	CLIENT_IN_LOBBY,
	HOST_IN_LOBBY,
	INGAME
};

class GameClient
{
public:
	GameClient(Game* game);
	~GameClient();

	void runFrame();

	bool isQuit();

	SDL_Renderer* getRenderer();

	Input* getInput();

	ResourceManager* getResourceManager();

	void changeGameClientState(GameClientState game_client_state);

	void joinLobby(CSteamID steam_id_lobby);

	CSteamID getThisUserSteamId();

private:
	// lobby handling

	// the name of the lobby we're connected to
	CSteamID _steam_id_lobby;

	// Id of the user on this client.
	CSteamID _steam_id_this_user;

	// callback for when we're creating a new lobby
	void OnLobbyCreated(LobbyCreated_t *pCallback, bool bIOFailure);
	CCallResult<GameClient, LobbyCreated_t> _steam_call_result_lobby_created;

	// callback for when we've joined a lobby
	void OnLobbyEntered(LobbyEnter_t *pCallback, bool bIOFailure);
	CCallResult<GameClient, LobbyEnter_t> _steam_call_result_lobby_entered;

	Game* _game;
	GameServer* _game_server;

	SDL_Renderer* _renderer;
	Input* _input;
	ResourceManager* _resource_manager;

	Lobby* _lobby;

	MainMenu* _main_menu;
	CreateGameMenu* _create_game_menu;
	LobbyMenu* _lobby_menu;
	BrowseServerMenu* _browse_server_menu;

	GameClientState _game_client_state;

	// Steam UserStats interface
	ISteamUserStats *_steam_user_stats;

	bool _quit;

	Timer t;
};

