#ifndef MapaVirtual_H
#define MapaVirtual_H
#include "checkML.h"
#include <SDL.h>
#include "Tile.h"

class MapaVirtual
{
public:
	virtual bool colisiones(SDL_Rect box) = 0;

	virtual void draw()const = 0;

	virtual bool touchesWall(SDL_Rect box) = 0;

	virtual inline Tile** getTileMap() = 0; 
	virtual inline SDL_Rect getCamera() const = 0;
	virtual inline int getXSpawn() const = 0;
	virtual inline int getYSpawn() const = 0;

	virtual Tile * GetTileAt(int x, int y) = 0;
	
	virtual bool tileColision(Tile * tile) = 0;

};

#endif