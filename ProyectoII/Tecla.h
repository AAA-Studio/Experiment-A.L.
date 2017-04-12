#ifndef _H_Tecla_H_
#define _H_Tecla_H_
#include "Entidad.h"

typedef int CallBack_t(int num);

class Tecla : public Entidad
{
public:
	Tecla(Juego* pJ, int x, int y, Texturas_t textura, Efectos_t efecto, CallBack_t * cb, int numero);
	virtual void onInput();
	~Tecla();

protected:
	CallBack_t * cboton;
	int numero;
	bool dentro(int x, int y)const;//Comprueba si se ha hecho click en el objeto
};
#endif

