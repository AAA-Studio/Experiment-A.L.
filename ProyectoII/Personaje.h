#ifndef Personaje_H
#define Personaje_H
#include "checkML.h"
#include "Entidad.h"


class Personaje : public Entidad
{
public:
	Personaje(Juego*pJ, int x, int y, Texturas_t color, Efectos_t efecto);//Constructora
	virtual ~Personaje();//Destructora

	virtual void update();//Actualiza el estado y devuelve false si el globo queda desinflado

};
#endif