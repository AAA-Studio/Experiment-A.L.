#ifndef Tile_H
#define Tile_H
#include <SDL.h>
#include "Juego.h"
class Tile
{
public:
	//Inicializa posicion y tipo
	Tile(int x, int y, int tileType, Juego * pJ);

	void render(const SDL_Rect& camera) const;

	inline int getType() const { return mType; };
	inline SDL_Rect getBox() const{ return mBox; };
	
private:
	SDL_Rect mBox;//Caja de colisiones
	Juego * pJuego;

	//Tipo de tile
	int mType;
};
#endif