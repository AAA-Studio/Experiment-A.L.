#ifndef MundoVirtual_H
#define MundoVirtual_H
#include "checkML.h"
#include "EstadoJuego.h"
#include "EntidadJuego.h"
#include "Juego.h"



//Clase abstracta que hereda de la raiz EstadoJuego
class MundoVirtual : public EstadoJuego
{
public:
	virtual void onInput(SDL_Event &e) = 0;

	virtual bool checkCollision(SDL_Rect a, SDL_Rect b) = 0;

	virtual void añadeObjeto(EntidadJuego * obj) = 0;

	virtual EntidadJuego * compruebaColisionObjetos() = 0;

	virtual Juego* getPJ()const  = 0;

	virtual void destruyeLlave(EntidadJuego * llave) = 0;

};

#endif