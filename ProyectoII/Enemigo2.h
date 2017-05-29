#ifndef _H_Enemigo2_H
#define _H_Enemigo2_H
#include "Entidad.h"
#include "MundoVirtual.h"

class Enemigo2 : public Entidad
{
public:
	Enemigo2(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto);


	virtual void update();
	inline void restaVida() { vida--; };
	inline float getVida()const { return vida; };
	virtual void mover(int x, int y){}

	~Enemigo2();

protected:
	int vida, x, y;
	int maxX, maxY;
	bool direccion; //false = izquierda, true = derecha
	bool pasivo; //el enemigo patrulla o ataca segun este en modo pasivo o no
	bool volviendo; //el enemigo vuelve a su posicion original si tiene que volver
	MundoVirtual* pMundo;
	float angulo, incrX, incrY;
	SDL_Rect rectPJ; // rect del personaje

	void patrulla();
	void ataque();
	void perseguir();
	void checkPersonaje();
	void volver();
};

#endif

