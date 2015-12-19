#include "Game.h"

int main()
{

	Game game;
	if (game.init())
	{
		game.gameLoop();
	}
	
	while (true)
	{

	}

	return 0;
}