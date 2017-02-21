#ifndef Boton_H
#define Boton_H
#include "checkML.h"
#include "Entidad.h"

typedef void CallBack_t(Juego* jg);

class Boton : public Entidad
{
public:
	Boton(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto, CallBack_t * cb);
	~Boton();
	virtual bool onClick();
	virtual void update(){};

private:
	CallBack_t * cboton;

};

#endif