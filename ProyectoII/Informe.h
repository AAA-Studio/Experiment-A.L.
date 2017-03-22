#ifndef _H_Informe_H_
#define _H_Informe_H_
#include "Entidad.h"
class Informe : public Entidad
{
public:
	Informe(Juego* pJ, int x, int y, Texturas_t textura, Efectos_t efecto, Texturas_t textura2);
	virtual void update(){}
	virtual void coger();
	~Informe();
protected:
	Texturas_t text;
	
};
#endif
