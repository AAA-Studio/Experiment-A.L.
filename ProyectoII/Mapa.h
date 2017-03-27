#ifndef Mapa_H
#define Mapa_H
#include "Juego.h"
#include <SDL.h>
#include "Tile.h"
#include "MundoVirtual.h"
#include <fstream>
#include <string>


class Mapa
{
public:
	Mapa(Juego*pJ, MundoVirtual * pM, string mapa); ////
	~Mapa();


	//Checks collision box against set of tiles
	bool touchesWall(SDL_Rect box);
	void draw()const;
	Tile** getTileMap(){ return tileMap; };
	SDL_Rect getCamera(){ return camera; };
	Juego * pJuego;
	MundoVirtual * pMundo;
	bool cargarMapa();
private:
	int nivel = 0;
	SDL_Rect camera;
	Tile* tileMap[TOTAL_TILES];
	string nombreMapa;
	

};
#endif

