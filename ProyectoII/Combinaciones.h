#ifndef _H_Combinaciones_H_
#define _H_Combinaciones_H_
#include "Menu.h"
#include "EntidadJuego.h"
#include "Juego.h"
#include <string>
#include "MundoVirtual.h"

class Combinaciones : public Menu
{
public:
	Combinaciones(Juego* juego, string combinacion, int puerta);

	virtual void draw() const;
	virtual void update();
	virtual void onInput(SDL_Event &e);
	~Combinaciones();

protected:
	void initObjetos();
	vector <EntidadJuego*> objetos;
	string combTecleada; //combinacion tecleada por el jugador
	string combinacion; //combinacion correcta
	bool acierto;
	int puerta;
	int intentos;
	MundoVirtual * pMundo;
};
#endif

