#include "Lobby.h"

#include "GameClient.h"
#include "ResourceManager.h"

#include <iostream>
#include <string>


Lobby::Lobby(GameClient* game_client) : m_CallbackPersonaStateChange(this, &Lobby::OnPersonaStateChange),
										m_CallbackLobbyDataUpdate(this, &Lobby::OnLobbyDataUpdate),
										m_CallbackChatDataUpdate(this, &Lobby::OnLobbyChatUpdate)
{
	_game_client = game_client;
}

Lobby::~Lobby()
{

}

void Lobby::runFrame()
{
	render();
	input();
	update();

}

void Lobby::setLobbySteamID(const CSteamID &steam_id_lobby)
{
	_steam_id_lobby = steam_id_lobby;
}

void Lobby::render()
{
	for (int i = 0; i < _players.size(); i++)
	{
		_players.at(i).text->render(100, 100 + i * 100);
	}
}
void Lobby::input()
{

}

void Lobby::update()
{

}

//-----------------------------------------------------------------------------
// Purpose: Handles a user in the lobby changing their name or details
//			( note: joining and leaving is handled below by CLobby::OnLobbyChatUpdate() )
//-----------------------------------------------------------------------------
void Lobby::OnPersonaStateChange(PersonaStateChange_t *pCallback)
{
	// callbacks are broadcast to all listeners, so we'll get this for every friend who changes state
	// so make sure the user is in the lobby before acting
	if (!SteamFriends()->IsUserInSource(pCallback->m_ulSteamID, _steam_id_lobby))
		return;

	std::cout << "OnPersonaStateChange" << std::endl;

}


//-----------------------------------------------------------------------------
// Purpose: Handles lobby data changing
//-----------------------------------------------------------------------------
void Lobby::OnLobbyDataUpdate(LobbyDataUpdate_t *pCallback)
{
	
	// callbacks are broadcast to all listeners, so we'll get this for every lobby we're requesting
	if (_steam_id_lobby != pCallback->m_ulSteamIDLobby)
		return;

	std::cout << "OnLobbyDataUpdate" << std::endl;
	

	//Clear old list of players
	for (int i = 0; i < _players.size(); i++)  
	{
		if (_players.at(i).text)
		{
			delete _players.at(i).text;
			_players.at(i).text = nullptr;
		}
	}

	_players.clear();

	// list of users in lobby
	// iterate all the users in the lobby and show their details
	int nr_of_players = SteamMatchmaking()->GetNumLobbyMembers(_steam_id_lobby);

	if (SteamMatchmaking()->GetLobbyOwner(_steam_id_lobby) == _game_client->getThisUserSteamId())
	{
		_is_host = true;
	}
	
	for (int i = 0; i < nr_of_players; i++)
	{
		CSteamID steamIDLobbyMember = SteamMatchmaking()->GetLobbyMemberByIndex(_steam_id_lobby, i);

		// we get the details of a user from the ISteamFriends interface
		const char *pchName = SteamFriends()->GetFriendPersonaName(steamIDLobbyMember);
		
		if (pchName && *pchName)
		{
			PlayerInfo p;
			p.isHost = false;
			p.player_name = pchName;
			p.text = _game_client->getResourceManager()->getTextureText(p.player_name, { 0xFF, 0xFF, 0xFF }, 20);
			_players.push_back(p);
		}
	}

	//virtual CSteamID GetLobbyOwner(CSteamID steamIDLobby) = 0;

	/*
	std::cout << SteamMatchmaking()->GetLobbyData(_steam_id_lobby, "lobby_name") << std::endl;
	std::cout << SteamMatchmaking()->GetLobbyData(_steam_id_lobby, "host_name") << std::endl;
	std::cout << SteamMatchmaking()->GetLobbyData(_steam_id_lobby, "map_name") << std::endl;
	std::cout << std::stoi(SteamMatchmaking()->GetLobbyData(_steam_id_lobby, "max_nr_of_players")) << std::endl;
	std::cout << SteamMatchmaking()->GetNumLobbyMembers(_steam_id_lobby) << std::endl;
	*/
}


//-----------------------------------------------------------------------------
// Purpose: Handles users in the lobby joining or leaving
//-----------------------------------------------------------------------------
void Lobby::OnLobbyChatUpdate(LobbyChatUpdate_t *pCallback)
{
	
	// callbacks are broadcast to all listeners, so we'll get this for every lobby we're requesting
	if (_steam_id_lobby != pCallback->m_ulSteamIDLobby)
		return;

	std::cout << "OnLobbyChatUpdate" << std::endl;
}

void Lobby::setHost(bool value)
{
	_is_host = value;
}

bool Lobby::isHost()
{
	return _is_host;
}
