#include "Tile.h"

Tile::Tile(int x, int y, int tileType, Juego * pJ)
{
	pJuego = pJ;
	//Get the offsets
	mBox.x = x;
	mBox.y = y;

	//Set the collision box
	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;

	//Get the tile type
	mType = tileType;
}
bool colision(SDL_Rect a, SDL_Rect b){
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	return !(bottomA <= topB || topA >= bottomB || rightA <= leftB || (leftA >= rightB));
}

void Tile::render(const SDL_Rect& camera) const
{
	//Show the tile
	//if (colision(mBox,camera))
	pJuego->getResources()->getTextura(JuegoSDL::TTilemap)->draw(pJuego->getRender(), mBox, mBox.x - camera.x, mBox.y - camera.y, &pJuego->getRectTile(mType));

}

