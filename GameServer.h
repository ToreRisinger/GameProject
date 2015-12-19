#pragma once

class GameClient;

class GameServer
{
public:
	GameServer(GameClient* game_client);
	~GameServer();

	void runFrame();

private:
	GameClient* _game_client;
};

