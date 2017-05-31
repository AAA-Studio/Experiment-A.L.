#ifndef _H_Enemigo4_H_
#define _H_Enemigo4_H_
#include "Enemigo.h"
#include "MundoVirtual.h"


class Enemigo4 : public Enemigo
{
public:
	Enemigo4(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto);
	virtual void update();
		
	
	~Enemigo4();

protected:
	
	
	//bool rodeado;
	bool rodeando;


	virtual void ataque();
	
};

#endif