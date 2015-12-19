#pragma once

#include <SDL.h>
#include <string>
#include <SDL.h>

class Texture
{
public:
	Texture(SDL_Renderer* renderer, int width, int height, SDL_Texture* texture);
	~Texture();

	int getWidth();
	int getHeight();
	SDL_Texture* getTexture();
	void render(int x, int y, int width, int height);
	void render(int x, int y);

private:
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;
	int _width;
	int _height;
};
