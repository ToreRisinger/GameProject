#include "LobbyMenuClient.h"

#include "MenuButton.h"
#include "Texture.h"
#include "Game.h"
#include "ResourceManager.h"
#include <iostream>

LobbyMenuClient::LobbyMenuClient(GameClient* game_client) : m_CallbackPersonaStateChange(this, &LobbyMenuClient::OnPersonaStateChange),
															m_CallbackLobbyDataUpdate(this, &LobbyMenuClient::OnLobbyDataUpdate),
															m_CallbackChatDataUpdate(this, &LobbyMenuClient::OnLobbyChatUpdate)
{
	_game_client = game_client;

	_texture_background = _game_client->getResourceManager()->getTexture("texture_background_main_menu");

	_menu_button1 = new MenuButton(_game_client, (WINDOW_WIDTH / 2) - 100, 600, 200, 55, 38, "Back", "texture_menu_button", "texture_menu_button_highlighted");
}

LobbyMenuClient::~LobbyMenuClient()
{

}


void LobbyMenuClient::runFrame()
{
	render();
	update();
	input();
}

void LobbyMenuClient::render()
{
	_texture_background->render(0, 0);

	_menu_button1->render();
}

void LobbyMenuClient::input()
{
	_menu_button1->input();
	if (_menu_button1->isPressed())
		_game_client->changeGameClientState(BROWSE_SERVERS);

}

void LobbyMenuClient::update()
{
	_menu_button1->update();
}

//-----------------------------------------------------------------------------
// Purpose: Sets the ID of the lobby to display
//-----------------------------------------------------------------------------
void LobbyMenuClient::SetLobbySteamID(const CSteamID &steam_id_lobby)
{
	_steam_id_lobby = steam_id_lobby;
}

//-----------------------------------------------------------------------------
// Purpose: Handles a user in the lobby changing their name or details
//			( note: joining and leaving is handled below by CLobby::OnLobbyChatUpdate() )
//-----------------------------------------------------------------------------
void LobbyMenuClient::OnPersonaStateChange(PersonaStateChange_t *pCallback)
{
	// callbacks are broadcast to all listeners, so we'll get this for every friend who changes state
	// so make sure the user is in the lobby before acting
	if (!SteamFriends()->IsUserInSource(pCallback->m_ulSteamID, _steam_id_lobby))
		return;

	std::cout << "OnPersonaStateChange" << std::endl;

	// rebuild the menu
	//m_pMenu->Rebuild(m_steamIDLobby);
}


//-----------------------------------------------------------------------------
// Purpose: Handles lobby data changing
//-----------------------------------------------------------------------------
void LobbyMenuClient::OnLobbyDataUpdate(LobbyDataUpdate_t *pCallback)
{
	// callbacks are broadcast to all listeners, so we'll get this for every lobby we're requesting
	if (_steam_id_lobby != pCallback->m_ulSteamIDLobby)
		return;

	std::cout << SteamMatchmaking()->GetLobbyData(_steam_id_lobby, "lobby_name") << std::endl;
	std::cout << SteamMatchmaking()->GetLobbyData(_steam_id_lobby, "host_name") << std::endl;
	std::cout << SteamMatchmaking()->GetLobbyData(_steam_id_lobby, "map_name") << std::endl;
	std::cout << std::stoi(SteamMatchmaking()->GetLobbyData(_steam_id_lobby, "max_nr_of_players")) << std::endl;
	//std::cout << std::stoi(SteamMatchmaking()->GetLobbyData(_steam_id_lobby, "nr_of_players")) << std::endl;
	std::cout << SteamMatchmaking()->GetNumLobbyMembers(_steam_id_lobby) << std::endl;


	// set the heading
	//m_pMenu->SetHeading(SteamMatchmaking()->GetLobbyData(m_steamIDLobby, "name"));

	// rebuild the menu
	//m_pMenu->Rebuild(m_steamIDLobby);
}


//-----------------------------------------------------------------------------
// Purpose: Handles users in the lobby joining or leaving
//-----------------------------------------------------------------------------
void LobbyMenuClient::OnLobbyChatUpdate(LobbyChatUpdate_t *pCallback)
{
	// callbacks are broadcast to all listeners, so we'll get this for every lobby we're requesting
	if (_steam_id_lobby != pCallback->m_ulSteamIDLobby)
		return;

	std::cout << "OnLobbyDataUpdate" << std::endl;

	// rebuild the menu
	//m_pMenu->Rebuild(m_steamIDLobby);


	//int cLobbyMembers = SteamMatchmaking()->GetNumLobbyMembers(m_steamIDLobby);
	//for (int i = 0; i < cLobbyMembers; i++)
	//{
		//CSteamID steamIDLobbyMember = SteamMatchmaking()->GetLobbyMemberByIndex(m_steamIDLobby, i);

		// ignore yourself.
		//if (SteamUser()->GetSteamID() == steamIDLobbyMember)
			//continue;

	//}
}
