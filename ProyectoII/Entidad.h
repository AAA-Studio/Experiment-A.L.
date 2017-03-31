#ifndef Entidad_H
#define Entidad_H
#include "checkML.h"
#include "EntidadJuego.h"
#include "SDL.h"
#include "Juego.h"
//Clase abstracta que hereda de la raiz ObjetoJuego e implementa utilidades para las subclases
class Entidad : public EntidadJuego
{
public:

	Entidad(Juego*pJ, double x, double y, Texturas_t textura, Efectos_t efecto, Objetos_t tipo);

	virtual ~Entidad();

	virtual void draw() const;
	virtual void onInput() {};
	virtual void update() {};

	SDL_Rect getRect()const{ return rect; };
	Objetos_t getType() const  { return type; };


protected:

	Juego * pJuego;//Sustituye al puntero a la textura y al renderizador de la clase globo
	Texturas_t pTextura;
	Efectos_t sonido;
	Objetos_t type;

	SDL_Rect rect;//Rectángulo para cada textura
};

#endif
