#include "LobbyBrowser.h"

#include "GameClient.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "LobbyBrowseButton.h"
#include "Keys.h"
#include "Input.h"

#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

LobbyBrowser::LobbyBrowser(GameClient* game_client)
{
	_game_client = game_client;

	_texture_background = _game_client->getResourceManager()->getTexture("texture_background_lobby_broswer");

	_y = 120;
	_x = WINDOW_WIDTH / 2 - _texture_background->getWidth() / 2;

	int button_width = _texture_background->getWidth() / 3;

	_game_name_button = new MenuButton(_game_client, _x, 120, button_width, 32, 22, "Game Name", "texture_lobby_browser_button_black", "texture_lobby_browser_button_black_highlighted");
	_map_name_button = new MenuButton(_game_client, _x + button_width, 120, button_width, 32, 22, "Map", "texture_lobby_browser_button", "texture_lobby_browser_button_highlighted");
	_nr_of_players_button = new MenuButton(_game_client, _x + button_width * 2, 120, button_width, 32, 22, "Players", "texture_lobby_browser_button", "texture_lobby_browser_button_highlighted");

	_pressed1 = false;
	_pressed2 = false;
	_pressed3 = false;

	_first_element_in_list = 0;
}

LobbyBrowser::~LobbyBrowser()
{

}

void LobbyBrowser::runFrame()
{
	update();
	render();
	input();
	
}

void LobbyBrowser::render()
{
	_texture_background->render(_x, _y);

	_game_name_button->render();
	_map_name_button->render();
	_nr_of_players_button->render();

	for (int i = _first_element_in_list; i < _lobby_list.size() && i < 10 + _first_element_in_list; i++)
	{
		_lobby_list.at(i).second->render();
	}
}

void LobbyBrowser::toupper(std::string &s) {
	for (char &c : s)
		c = std::toupper(c);
}


bool LobbyBrowser::strcasecmp(std::string lhs, std::string rhs) {
	toupper(lhs); toupper(rhs);
	return lhs < rhs;
}

void  LobbyBrowser::swap(std::pair<Lobby_t, LobbyBrowseButton*> & lhs, std::pair<Lobby_t, LobbyBrowseButton*> & rhs)
{
	std::pair<Lobby_t, LobbyBrowseButton*> tmp = lhs;
	lhs = rhs;
	rhs = tmp;
}

void LobbyBrowser::input()
{
	if (_game_client->getInput()->getKeyDown(MOUSE_WHEEL_UP)) {
		if (_first_element_in_list > 0) {
			_first_element_in_list--;
		}
	}
	else if (_game_client->getInput()->getKeyDown(MOUSE_WHEEL_DOWN)) {
		
		
		int size = _lobby_list.size();
		if (size > 10 && _first_element_in_list < size - 10) {
			_first_element_in_list++;
		}
	}

	_game_name_button->input();
	if (_game_name_button->isPressed()) {
		if (_pressed1 == false) {
			for (int i = 0; i < _lobby_list.size(); i++)
			{
				for (int j = 0; j < _lobby_list.size() - 1; j++)
				{
					if (strcasecmp(_lobby_list.at(j).first.lobby_name, _lobby_list.at(j + 1).first.lobby_name))
						swap(_lobby_list.at(j), _lobby_list.at(j + 1));
				}
			}
		}
		else if (_pressed1 == true) {
			for (int i = 0; i < _lobby_list.size(); i++)
			{
				for (int j = 0; j < _lobby_list.size() - 1; j++)
				{
					if (!strcasecmp(_lobby_list.at(j).first.lobby_name, _lobby_list.at(j + 1).first.lobby_name))
						swap(_lobby_list.at(j), _lobby_list.at(j + 1));
				}
			}
		}

		_pressed1 = !_pressed1;
	}

	_map_name_button->input();
	if (_map_name_button->isPressed()) {
		if (_pressed2 == false) {
			_pressed2 = true;
			for (int i = 0; i < _lobby_list.size(); i++)
			{
				for (int j = 0; j < _lobby_list.size() - 1; j++)
				{
					if (strcasecmp(_lobby_list.at(j).first.map_name, _lobby_list.at(j + 1).first.map_name))
						swap(_lobby_list.at(j), _lobby_list.at(j + 1));
				}
			}
		}
		else if (_pressed2 == true) {
			_pressed2 = false;
			for (int i = 0; i < _lobby_list.size(); i++)
			{
				for (int j = 0; j < _lobby_list.size() - 1; j++)
				{
					if (!strcasecmp(_lobby_list.at(j).first.map_name, _lobby_list.at(j + 1).first.map_name))
						swap(_lobby_list.at(j), _lobby_list.at(j + 1));
				}
			}
		}
	}

	_nr_of_players_button->input();
	if (_nr_of_players_button->isPressed()) {
		if (_pressed3 == false) {
			_pressed3 = true;
			std::sort(_lobby_list.begin(), _lobby_list.end(),
				[](const std::pair<Lobby_t, LobbyBrowseButton*> & a, const std::pair<Lobby_t, LobbyBrowseButton*> & b) -> bool
			{
				return a.first.nr_of_players > b.first.nr_of_players;
			});
		}
		else if (_pressed3 == true) {
			_pressed3 = false;
			std::sort(_lobby_list.begin(), _lobby_list.end(),
				[](const std::pair<Lobby_t, LobbyBrowseButton*> & a, const std::pair<Lobby_t, LobbyBrowseButton*> & b) -> bool
			{
				return a.first.nr_of_players < b.first.nr_of_players;
			});
		}
	}

	int pressed_index = -1;
	for (int i = _first_element_in_list; i < _lobby_list.size() && i < _first_element_in_list + 10; i++)
	{
		_lobby_list.at(i).second->input();
		if (_lobby_list.at(i).second->isPressed()) {
			pressed_index = i;
		}
	}

	if (pressed_index != -1)
	{
		for (int i = 0; i < _lobby_list.size(); i++)
		{
			if (i == pressed_index)
				_lobby_list.at(i).second->setSelect(true);
			else
				_lobby_list.at(i).second->setSelect(false);
		}
	}
}
 
void LobbyBrowser::update()
{
	for (int i = _first_element_in_list; i < _lobby_list.size() && i < 10 + _first_element_in_list; i++)
	{
		_lobby_list.at(i).second->setY(120 + 32 + 32 * (i - _first_element_in_list));
	}
}

void LobbyBrowser::setLobbyList(std::vector<Lobby_t> lobby_list)
{
	for (int i = 0; i < lobby_list.size(); i++)
	{
		_lobby_list.push_back({ lobby_list.at(i), new LobbyBrowseButton(_game_client, _x + 3, 150, _texture_background->getWidth() - 6, 32, 22,
			lobby_list.at(i).lobby_name,
			lobby_list.at(i).map_name,
			std::to_string(lobby_list.at(i).nr_of_players) + "/" + std::to_string(lobby_list.at(i).max_nr_of_players),
			"texture_lobby_browser_entry_button", "texture_lobby_browser_entry_button_highlighted", "texture_lobby_browser_entry_button_selected") });
	}

}

void LobbyBrowser::clearLobbyList()
{
	for (int i = 0; i < _lobby_list.size(); i++)
	{
		delete _lobby_list.at(i).second;
		_lobby_list.at(i).second = nullptr;
	}

	_lobby_list.clear();
	_first_element_in_list = 0;
}

void LobbyBrowser::joinLobby()
{
	for (int i = 0; i < _lobby_list.size(); i++)
	{
		if(_lobby_list.at(i).second->isSelected())
		{
			_game_client->changeGameClientState(JOINING_LOBBY);
			_game_client->joinLobby(_lobby_list.at(i).first.steam_id_lobby);
			return;
		}
	}
}
