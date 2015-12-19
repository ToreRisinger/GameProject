#pragma once

#include <steamclientpublic.h>
#include <steam_api.h>

class GameClient;
class MenuButton;
class Texture;

class LobbyMenuClient
{
public:
	LobbyMenuClient(GameClient* game_client);
	~LobbyMenuClient();

	void runFrame();
	void SetLobbySteamID(const CSteamID &steam_id_lobby);

private:
	void render();
	void input();
	void update();

	GameClient* _game_client;

	MenuButton* _menu_button1;

	Texture* _texture_background;

	CSteamID _steam_id_lobby;

	// user state change handler
	STEAM_CALLBACK(LobbyMenuClient, OnPersonaStateChange, PersonaStateChange_t, m_CallbackPersonaStateChange);

	// lobby state change handler
	STEAM_CALLBACK(LobbyMenuClient, OnLobbyDataUpdate, LobbyDataUpdate_t, m_CallbackLobbyDataUpdate);
	STEAM_CALLBACK(LobbyMenuClient, OnLobbyChatUpdate, LobbyChatUpdate_t, m_CallbackChatDataUpdate);
};

