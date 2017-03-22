#ifndef Mundo_H
#define Mundo_H
#include "checkML.h"
#include "Estado.h"
#include "Tile.h"
#include <SDL.h>

//-----------------------------------------------------


//Clase abstracta que hereda de la raiz ObjetoJuego e implementa utilidades para las subclases
class Mundo : public Estado
{
protected:
	virtual void draw() const;
	virtual void onInput(SDL_Event &e);
	virtual void update();

public:
	Mundo(Juego * pJ);
	virtual ~Mundo();
	void newBaja(EntidadJuego * po); // Los objetos informarán al juego cuando causen baja


	//------------------------------------------------
	//Box collision detector
	bool checkCollision(SDL_Rect a, SDL_Rect b);

	//Checks collision box against set of tiles
	bool touchesWall(SDL_Rect box);

	SDL_Rect camera;

	Tile* tileMap[TOTAL_TILES];

	bool setTiles();

	Tile** getTileMap(){ return tileMap; };

	//------------------------------------------------
private:
	bool pausa;
	void initObjetos();
	EntidadJuego* bolsillo;
	void soltar();

};

#endif
