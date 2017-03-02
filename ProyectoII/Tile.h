#pragma once
#include <SDL.h>
#include "Juego.h"
class Tile
{
public:
	//Initializes position and type
	Tile(int x, int y, int tileType, Juego * pJ);

	//Shows the tile
	void render(const SDL_Rect& camera);

	//Get the tile type
	int getType();

	//Get the collision box
	SDL_Rect getBox();

private:
	//The attributes of the tile
	SDL_Rect mBox;
	Juego * pJuego;

	//The tile type
	int mType;
};