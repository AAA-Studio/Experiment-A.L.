#ifndef Llave_H_
#define Llave_H_
#include "checkML.h"
#include "Entidad.h"


class Llave : public Entidad
{
public:
	Llave(Juego* pJ, int x, int y, Texturas_t textura, Efectos_t efecto);
	~Llave();
	virtual void update(){};

};

#endif