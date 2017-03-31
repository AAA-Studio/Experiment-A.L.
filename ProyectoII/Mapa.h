#ifndef Mapa_H
#define Mapa_H
#include <SDL.h>
#include "Tile.h"
#include "MundoVirtual.h"
#include <fstream>
#include <string>


class Mapa
{
public:
	Mapa(MundoVirtual * pM, string mapa); ////
	~Mapa();

	//Checks collision box against set of tiles
	bool touchesWall(SDL_Rect box);
	void draw()const;

	//--------------------GETTER----------------
	inline Tile** getTileMap() { return tileMap; };
	inline SDL_Rect getCamera() const{ return camera; };

private:
	MundoVirtual * pMundo;
	string nombreMapa;

	SDL_Rect camera;
	Tile* tileMap[TOTAL_TILES];

	bool cargarMapa();


};
#endif

