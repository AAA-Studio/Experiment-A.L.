#ifndef Mapa_H
#define Mapa_H
#include <SDL.h>
#include "Tile.h"
#include "MundoVirtual.h"
#include <fstream>
#include <string>
#include "MapaVirtual.h"


class Mapa : public MapaVirtual
{
public:
	Mapa(MundoVirtual * pM, string mapa); ////
	~Mapa();

	//Checks collision box against set of tiles
	bool colisiones(SDL_Rect box);
	void draw()const;

	bool touchesWall(SDL_Rect box);

	//--------------------GETTER----------------
	inline Tile** getTileMap()  { return tileMap; };
	inline SDL_Rect getCamera() const{ return camera; };
	inline int getXSpawn() const{ return x; };
	inline int getYSpawn() const{ return y; };


	Tile * GetTileAt(int x, int y) {
		if (tileMap == NULL || x < 0 ||x>= LEVEL_WIDTH || y < 0 ||y>= LEVEL_HEIGHT) 
			return NULL;
		
		return tileMap[y * LEVEL_WIDTH + x];
	}

	bool tileColision(Tile * tile);


private:
	MundoVirtual * pMundo;
	Juego * pJuego;
	string nombreMapa;
	SDL_Rect camera;
	Tile* tileMap[TOTAL_TILES];

	bool cargarMapa();
	void buscaSpawn();

	int x, y;

	int nivel = 0;
};
#endif
