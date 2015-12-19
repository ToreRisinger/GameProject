#include "ResourceManager.h"
#include <SDL_image.h>
#include "Game.h"
#include <iostream>

ResourceManager::ResourceManager(Game* game)
{
	_game = game;

	//Load all textures in the game
	//Insert them into a hashmap
	std::pair<std::string, Texture*> p;

	initTTF();

	p = {"texture_background_main_menu", loadTexture("texture_background_main_menu")};
	_textures.insert(p);

	p = { "texture_menu_button", loadTexture("texture_menu_button") };
	_textures.insert(p);
	p = { "texture_menu_button_highlighted", loadTexture("texture_menu_button_highlighted") };
	_textures.insert(p);

	p = { "texture_background_lobby_broswer", loadTexture("texture_background_lobby_broswer") };
	_textures.insert(p);

	p = { "texture_lobby_browser_button", loadTexture("texture_lobby_browser_button") };
	_textures.insert(p);
	p = { "texture_lobby_browser_button_highlighted", loadTexture("texture_lobby_browser_button_highlighted") };
	_textures.insert(p);

	p = { "texture_lobby_browser_button_black", loadTexture("texture_lobby_browser_button_black") };
	_textures.insert(p);
	p = { "texture_lobby_browser_button_black_highlighted", loadTexture("texture_lobby_browser_button_black_highlighted") };
	_textures.insert(p);

	p = { "texture_lobby_browser_entry_button", loadTexture("texture_lobby_browser_entry_button") };
	_textures.insert(p);
	p = { "texture_lobby_browser_entry_button_highlighted", loadTexture("texture_lobby_browser_entry_button_highlighted") };
	_textures.insert(p);
	p = { "texture_lobby_browser_entry_button_selected", loadTexture("texture_lobby_browser_entry_button_selected") };
	_textures.insert(p);
	
	

	
}

void ResourceManager::initTTF()
{
	for (int i = 0; i < 40; i++)
	{
		TTF_Font* font = TTF_OpenFont("./res/fonts/Calibri.ttf", i);
		if (font == NULL)
		{
			std::cout << "Failed to load lazy font! SDL_ttf Error: %s\n" << TTF_GetError() << std::endl;
		}
		else
			_fonts.push_back(font);
	}
}


ResourceManager::~ResourceManager()
{

}


Texture* ResourceManager::getTexture(std::string fileName)
{
	
	if (_textures.find(fileName) != _textures.end()) {
		return _textures.find(fileName)->second;
	}
	else
	{
		std::cout << "ERROR: ResourceManager, getTexture() could not load file: " << fileName << std::endl;
		return nullptr;
	}
		
}

/*
Texture* ResourceManager::loadTexture(int width, int height, int red, int green, int blue)
{
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = nullptr;

	//create image
	loadedSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

	//fill the image with the color
	SDL_FillRect(loadedSurface, NULL, SDL_MapRGB(loadedSurface->format, red, green, blue));

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	//make a texture from the image
	newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);

	if (newTexture == NULL)
	{
		printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
	}

	SDL_FreeSurface(loadedSurface);

	return new Texture(_renderer, width, height, newTexture);
}
*/

Texture* ResourceManager::loadTexture(std::string fileName)
{
	int width;
	int height;
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(("./res/textures/" + fileName + ".png").c_str());

	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image! SDL_image Error: " << "./res/textures/" << fileName << ".png " << IMG_GetError() << std::endl;
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(_game->renderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture from %s! SDL Error: %s\n" << "./res/textures/" << fileName << ".png" << SDL_GetError() << std::endl;
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	Texture* ret = new Texture(_game->renderer, width, height, newTexture);

	return ret;
}

SDL_Surface* ResourceManager::getMap(std::string fileName)
{
	int width;
	int height;
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedMapSurface = IMG_Load(("./res/maps/" + fileName + ".png").c_str());

	if (loadedMapSurface == NULL)
	{
		std::cout << "Unable to load image %s! SDL_image Error: %s\n" << "./res/textures/" << fileName << ".png" << IMG_GetError() << std::endl;
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedMapSurface, SDL_TRUE, SDL_MapRGB(loadedMapSurface->format, 0, 0xFF, 0xFF));

	}

	return loadedMapSurface;
}

Texture* ResourceManager::getTextureFromSurface(SDL_Surface* surface)
{
	int width;
	int height;
	//Create texture from surface pixels
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(_game->renderer, surface);
	if (newTexture == NULL)
	{
		std::cout << "Unable to create texture from surface! SDL Error: %s\n" << std::endl;
	}
	else
	{
		//Get image dimensions
		width = surface->w;
		height = surface->h;
	}

	Texture* ret = new Texture(_game->renderer, width, height, newTexture);

	return ret;
}

Texture* ResourceManager::getTextureText(std::string textureText, SDL_Color textColor, int size)
{
	TTF_Font* font = nullptr;

	font = _fonts.at(size - 1);
	int width;
	int height;
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = TTF_RenderText_Blended(font, textureText.c_str(), textColor);
	if (loadedSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(_game->renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(loadedSurface);
	}

	SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
	Texture* ret = new Texture(_game->renderer, width, height, newTexture);
	
	return ret;
}
