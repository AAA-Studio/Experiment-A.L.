#ifndef Mundo_H
#define Mundo_H
#include "checkML.h"
#include "MundoVirtual.h"
#include "EntidadJuego.h"
#include "Juego.h"

#include <SDL.h>
#include "Mapa.h"
#include "Personaje.h"



//Clase abstracta que hereda de la raiz ObjetoJuego e implementa utilidades para las subclases
class Mundo : public MundoVirtual
{
public:
	Mundo(Juego * pJ,string mapa);
	virtual ~Mundo();

	virtual void draw() const;
	virtual void onInput(SDL_Event &e);
	virtual void update();
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	inline Mapa* getMapa(){ return mapa; };
private:
	bool pausa;
	void initObjetos();
	void freeObjetos();

	Mapa * mapa;

	vector <EntidadJuego*> objetos;
	Personaje * psj;

	Juego * pJuego;

};

#endif
