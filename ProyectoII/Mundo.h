#ifndef Mundo_H
#define Mundo_H
#include "checkML.h"
#include "MundoVirtual.h"
#include "EntidadJuego.h"
#include "Juego.h"

#include <SDL.h>
#include "Mapa.h"


//Clase abstracta que hereda de la raiz ObjetoJuego e implementa utilidades para las subclases
class Mundo : public MundoVirtual
{
public:
	Mundo(Juego * pJ);
	virtual ~Mundo();

	virtual void draw() const;
	virtual void onInput(SDL_Event &e);
	virtual void update();

	void newBaja(EntidadJuego * po); // Los objetos informarán al juego cuando causen baja
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	inline Mapa* getMapa(){ return mapa; };
private:
	bool pausa;
	void initObjetos();
	void freeObjetos();

	Mapa * mapa;

	vector <EntidadJuego*> objetos;
	Juego * pJuego;

};

#endif
