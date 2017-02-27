#ifndef _H_Enemigo_H_
#define _H_Enemigo_H_
#include "checkML.h"
#include "Entidad.h"
#include "MathCore.h"
class Enemigo: public Entidad
{
public:
	Enemigo(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto);
	~Enemigo();

	double radius;
	Vector3 pos;
};
#endif
