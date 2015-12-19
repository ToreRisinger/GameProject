#include "Texture.h"

#include <iostream>
#include <SDL_image.h>

Texture::Texture(SDL_Renderer* renderer, int width, int height, SDL_Texture* texture) : _renderer{ renderer }, _width{ width }, _height{ height }, _texture{ texture }
{

}

Texture::~Texture()
{
	SDL_DestroyTexture(_texture);
	_texture = nullptr;
}

int Texture::getWidth()
{
	return _width;
}

int Texture::getHeight()
{
	return _height;
}

SDL_Texture* Texture::getTexture()
{
	return _texture;
}

void Texture::render(int x, int y, int width, int height)
{
	if (_texture != nullptr)
	{
		SDL_Rect renderRect = { x, y, width, height };
		SDL_RenderCopy(_renderer, _texture, NULL, &renderRect);
	}
}

void Texture::render(int x, int y)
{
	if (_texture != nullptr)
	{
		SDL_Rect renderRect = { x, y, _width, _height };
		SDL_RenderCopy(_renderer, _texture, NULL, &renderRect);
	}
}