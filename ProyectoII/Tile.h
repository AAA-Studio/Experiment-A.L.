#pragma once
#include <SDL.h>
#include "Juego.h"
class Tile
{
public:
	//Initializes position and type
	Tile(int x, int y, int tileType, Juego * pJ);

	//Shows the tile
	void render(const SDL_Rect& camera) const;

	//Get the tile type
	inline int getType() const {return mType;};

	//Get the collision box
	inline SDL_Rect getBox() const{ return mBox; };

private:
	//The attributes of the tile
	SDL_Rect mBox;
	Juego * pJuego;

	//The tile type
	int mType;
};