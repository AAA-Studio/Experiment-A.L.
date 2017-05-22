#ifndef Mapa_H
#define Mapa_H
#include <SDL.h>
#include "Tile.h"
#include "MundoVirtual.h"
#include <string>

class Mapa
{
public:
	Mapa(MundoVirtual * pM, string mapa);
	~Mapa();

	bool touchesWall(SDL_Rect box);
	bool touchesDoor(SDL_Rect box, int& tipo);

	void draw()const;

	//--------------------GETTER----------------
	inline Tile** getTileMap() { return tileMap; };
	inline int getXSpawn() const{ return x; };
	inline int getYSpawn() const{ return y; };


private:
	MundoVirtual * pMundo;
	Juego * pJuego;
	string nombreMapa;
	Tile* tileMap[TOTAL_TILES];
	bool Puerta1Abierta;
	int x, y;//Variables en las que se guarda la pos del Spawn del personaje
	//int nivel;

	bool cargarMapa();
	void buscaSpawn();
	void setCamera();//Pone la cámara en el centro de cada nivel cuando se pasa de una sala a otra
};
#endif
