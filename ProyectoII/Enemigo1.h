#ifndef _H_Enemigo1_H_
#define _H_Enemigo1_H_

#include "checkML.h"
#include "Enemigo.h"
#include <list>
#include "MundoVirtual.h"


class Enemigo1 : public Enemigo
{
public:
	Enemigo1(MundoVirtual*pJ, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto);
	~Enemigo1();

	virtual void update();
	

private:
	//MundoVirtual* pMundo;
	void disparo();
	//int vida;
	const float tiempoBala = 3000;
	Uint32 ultimaBala;
	float angulo;
};

#endif

