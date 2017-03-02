#ifndef Entidad_H
#define Entidad_H
#include "checkML.h"
#include "EntidadJuego.h"
#include "SDL.h"
#include "Mundo.h"

//Clase abstracta que hereda de la raiz ObjetoJuego e implementa utilidades para las subclases
class Entidad : public EntidadJuego
{
protected:
	//El update no se modifica

	Juego * pJuego;//Sustituye al puntero a la textura y al renderizador de la clase globo
	Texturas_t pTextura;
	Efectos_t sonido;

	double posX, posY;
	int  ancho, alto;
	SDL_Rect rect;//Rectángulo para cada textura

public:
	virtual void draw() const;
	virtual void onInput() {};

	const SDL_Rect getRect(){ return rect; }
	Entidad(Juego*pJ, double x, double y, Texturas_t textura, Efectos_t efecto);
	virtual ~Entidad();

};

#endif
