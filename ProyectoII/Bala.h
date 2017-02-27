#ifndef Boton_H
#define Boton_H
#include "checkML.h"
#include "Entidad.h"


class Bala : public Entidad
{
public:
	Bala(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto,int ang);
	~Bala();
	virtual void update();

private:
	int incrX,incrY;
	int velocidad;
	int angulo;

	void setAngulo();

};

#endif