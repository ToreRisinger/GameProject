#pragma once

class Input;
class GameClient;
class ResourceManager;
struct SDL_Renderer;
struct SDL_Window;

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

class Game
{
public:
	Game();
	~Game();

	bool init();
	void gameLoop();

	SDL_Window* window;
	SDL_Renderer* renderer;
	Input* input;
	ResourceManager* resource_manager;
	

private:
	void close();
	void clearScreen();
	void drawScreen();

	GameClient* _game_client;

	bool _quit;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
};
