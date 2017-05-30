#ifndef _H_Enemigo2_H
#define _H_Enemigo2_H
#include "Enemigo.h"
#include "MundoVirtual.h"



class Enemigo2 : public Enemigo
{
public:
	Enemigo2(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto, char dir);

	inline int DamePosAntX(){ return posXAnt; };
	inline int DamePosAntY(){ return posYAnt; };
	virtual void update();

	~Enemigo2();

protected:
	int vida, x, y;
	int maxX, maxY;
	bool direccion; //false = izquierda, true = derecha
	bool pasivo; //el enemigo patrulla o ataca segun este en modo pasivo o no
	bool volviendo; //el enemigo vuelve a su posicion original si tiene que volver

	float angulo, incrX, incrY;
	char eje;

	void patrulla();
	virtual void ataque();
	void checkPersonaje();
	void volver();
};

#endif

