#ifndef Menu_H
#define Menu_H
#include "checkML.h"
#include "EstadoJuego.h"
#include "Juego.h"
#include "EntidadJuego.h"

//Clase abstracta no pura que hereda de la raiz EstadoJuego
class Menu : public EstadoJuego
{

public:
	//Métodos
	Menu(Juego * pJ);
	virtual void onInput(SDL_Event &e);
	void freeObjetos();
	void update();
	void draw()const;

	//Atributos
	Juego * pJuego;
	vector <EntidadJuego*> objetos;

protected:
	void freeObjetos();

};

#endif