#pragma once


#include <steamclientpublic.h>
#include <steam_api.h>
#include <vector>

class GameClient;
class Texture;

struct PlayerInfo
{
	std::string player_name = "";
	Texture* text = nullptr;
	bool isHost = false;
};

class Lobby
{
public:
	Lobby(GameClient* game_client);
	~Lobby();

	void runFrame();
	void setLobbySteamID(const CSteamID &steam_id_lobby);

	void setHost(bool value);
	bool isHost();

private:
	void render();
	void input();
	void update();

	bool _is_host;
	
	std::vector<PlayerInfo> _players;

	GameClient* _game_client;
	
	CSteamID _steam_id_lobby;

	// user state change handler
	STEAM_CALLBACK(Lobby, OnPersonaStateChange, PersonaStateChange_t, m_CallbackPersonaStateChange);

	// lobby state change handler
	STEAM_CALLBACK(Lobby, OnLobbyDataUpdate, LobbyDataUpdate_t, m_CallbackLobbyDataUpdate);
	STEAM_CALLBACK(Lobby, OnLobbyChatUpdate, LobbyChatUpdate_t, m_CallbackChatDataUpdate);

};

