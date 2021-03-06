#ifndef Boton_H
#define Boton_H
#include "checkML.h"
#include "Entidad.h"

typedef void CallBack_t(Juego* jg);

class Boton : public Entidad
{
public:
	Boton(Juego*pJ, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto, CallBack_t * cb);
	~Boton();
	virtual void onInput();

private:
	CallBack_t * cboton;
	bool dentro(int x, int y)const;//Comprueba si se ha hecho click en el objeto
};

#endif