#ifndef Mapa_H
#define Mapa_H
#include "Juego.h"
#include <SDL.h>
#include "Tile.h"
#include <fstream>


class Mapa
{
public:
	Mapa(Juego*pJ);
	~Mapa();


	//Checks collision box against set of tiles
	bool touchesWall(SDL_Rect box);
	void draw()const;
	Tile** getTileMap(){ return tileMap; };
	bool cargarMapa();
	SDL_Rect getCamera(){ return camera; };
	Juego * pJuego;


private:
	SDL_Rect camera;
	Tile* tileMap[TOTAL_TILES];
};
#endif

