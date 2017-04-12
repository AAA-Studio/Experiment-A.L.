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

void Tile::render(const SDL_Rect& camera) const
{
	//Show the tile
	pJuego->getTextura(TTilemap)->draw(pJuego->getRender(),mBox, &pJuego->getRectTile(mType));

}
