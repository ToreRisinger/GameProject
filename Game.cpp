#include "Game.h"

#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL.h>
#undef main

#include "Timer.h"
#include "steam_api.h"
#include "steam_gameserver.h"
#include "Input.h"
#include "ResourceManager.h"
#include "GameClient.h"


/*
* GOOD LINKS:
* http://beej.us/guide/bgnet/output/html/multipage/index.html
*
*
*
*
*/

Game::Game()
{
	renderer = nullptr;
	window = nullptr;
}

Game::~Game()
{

}

void Game::gameLoop()
{
	_game_client = new GameClient(this);

	//FPS
	Timer timerSeconds;
	timerSeconds.start();
	int fps{};

	//Enable text input
	SDL_StartTextInput();

	_quit = false;	

	//GAMELOOP
	while (!_quit)
	{
		
		input->takeInput();

		clearScreen();

		_game_client->runFrame();
		if (_game_client->isQuit())
		{
			_quit = true;
		}

		drawScreen();

		fps++;
		if (timerSeconds.getElapsedTime() >= 1000)
		{
			timerSeconds.start();
			//system("CLS");
			std::cout << "Fps: " << fps << std::endl;
			fps = 0;
			
		}
	}

	close();
}

void Game::drawScreen()
{
	SDL_RenderPresent(renderer);
}

void Game::clearScreen()
{
	SDL_RenderClear(renderer);
}

bool Game::init()
{

	if (!SteamAPI_Init())
	{
		std::cout << "SteamAPI_Init returned false. "<< std::endl;
		return false;
	}

	// Ensure that the user has logged into Steam. This will always return true if the game is launched
	// from Steam, but if Steam is at the login prompt when you run your game from the debugger, it
	// will return false.
	if (!SteamUser()->BLoggedOn())
	{
		std::cout << "Steam user must be logged in to play this game (SteamUser()->BLoggedOn() returned false)" << std::endl;
		return false;
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize SDL_Error: %s\n" << SDL_GetError() << std::endl;
		return false;
	}

	//Create Window
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError() << std::endl;
		return false;
	}

	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError() << std::endl;
		return false;
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError() << std::endl;
		return false;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError() << std::endl;
		return false;
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0x0);

	input = new Input();
	resource_manager = new ResourceManager(this);

	return true;
}

void Game::close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	delete input;
	input = nullptr;

	delete resource_manager;
	resource_manager = nullptr;


	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}