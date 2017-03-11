#ifndef _H_Llave_H_
#define _H_Llave_H_
#include "Entidad.h"
class Llave : public Entidad
{
public:
	Llave(Juego* pJ, int x, int y, Texturas_t textura, Efectos_t efecto);
	virtual void update(){}
	virtual void coger();
	virtual void soltar(double x, double y);
	~Llave();
};
#endif