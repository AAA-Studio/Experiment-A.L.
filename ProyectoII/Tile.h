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
	inline int getType(){return mType;};

	//Get the collision box
	inline SDL_Rect getBox(){return mBox;};

private:
	//The attributes of the tile
	SDL_Rect mBox;
	Juego * pJuego;

	//The tile type
	int mType;
};