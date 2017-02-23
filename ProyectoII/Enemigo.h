#ifndef _H_Enemigo_H_
#define _H_Enemigo_H_
#include "checkML.h"
#include "Entidad.h"
class Enemigo: public Entidad
{
public:
	Enemigo(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto);
	virtual~Enemigo();
};
#endif
