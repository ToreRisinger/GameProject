#pragma once

#include <unordered_map>
#include "Texture.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

class Game;
class Texture;
struct SDL_Surface;
struct SDL_Colo;

class ResourceManager
{
public:
	ResourceManager(Game* game);
	~ResourceManager();

	Texture* getTexture(std::string fileName);
	Texture* getTextureText(std::string textureText, SDL_Color textColor, int size);

	Texture* getTextureFromSurface(SDL_Surface* surface);
	SDL_Surface* getMap(std::string fileName);

private:
	std::unordered_map<std::string, Texture*> _textures;

	//Texture* loadTexture(int width, int height, int red, int green, int blue);
	Texture* loadTexture(std::string fileName);
	void initTTF();

	Game* _game;

	std::vector<TTF_Font*> _fonts;
};

