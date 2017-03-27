#ifndef Menu_H
#define Menu_H
#include "checkML.h"
#include "Juego.h"
#include "EstadoJuego.h"
#include "EntidadJuego.h"

//Clase abstracta no pura que hereda de la raiz EstadoJuego
class Menu : public EstadoJuego
{

public:
	//Métodos
	Menu(Juego * pJ);
	virtual ~Menu(){};
	
	virtual void update();
	virtual void draw()const;
	virtual void onInput(SDL_Event &e);

protected:

	//Atributos
	Juego * pJuego;
	vector <EntidadJuego*> objetos;
	void freeObjetos();

};

#endif