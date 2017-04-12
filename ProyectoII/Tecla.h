#ifndef _H_Tecla_H_
#define _H_Tecla_H_
#include "Boton.h"

class Tecla : public Boton
{
public:
	Tecla(Juego* pJ, int x, int y, Texturas_t textura, Efectos_t efecto, CallBack_t * cb);
	virtual void onInput();
	~Tecla();

protected:
	void setNumero(int num){ num = numero; }
	int numero;
};
#endif

