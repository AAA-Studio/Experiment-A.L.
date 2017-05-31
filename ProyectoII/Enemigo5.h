#ifndef _H_Enemigo5_H_
#define _H_Enemigo5_H_

#include "Enemigo.h"
#include "MundoVirtual.h" 

class Enemigo5 : public Enemigo
{
public:
	Enemigo5(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto);
	~Enemigo5();

	// Este enemigo esta estatico cuando dispara al personaje
	// vuela a la posicion del frame antarior del personaje aleatoriamente
	virtual void update();

	inline int DamePosAntX(){ return posXAnt; };
	inline int DamePosAntY(){ return posYAnt; };
protected:

	bool rodeando;
	pair<float, float> destino;
	void disparar();
	void movimiento();
	SDL_Rect rectPJ; // rect del personaje

	const float tiempoBala = 1000;
	Uint32 ultimaBala;
	float angulo;
};
#endif