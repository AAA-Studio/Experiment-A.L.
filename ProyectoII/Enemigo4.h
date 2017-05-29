#ifndef _H_Enemigo4_H_
#define _H_Enemigo4_H_
#include "Entidad.h"
#include "MundoVirtual.h"

struct Direction2{
	int x;
	int y;
};
class Enemigo4 : public Entidad
{
public:
	Enemigo4(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto);
	virtual void update();
	inline void restaVida() { vida--; };
	inline float getVida()const { return vida; };
	virtual void mover(int x, int y){}
	void setPosChocando(int x, int y);
	void setDir(Direction2 direc){ dir = direc; };
	inline int DamePosAntX(){ return posXAnt; };
	inline int DamePosAntY(){ return posYAnt; };
	void chocarX(char x, bool chocando){ this->chocando = chocando; xCol = x; }
	void chocarY(char y, bool chocando){ this->chocando = chocando; yCol = y; }
	~Enemigo4();

protected:
	SDL_Rect rectPJ; // rect del personaje
	MundoVirtual* pMundo;
	Direction2 dir;
	int vida;
	char xCol, yCol;
	bool chocando;
	int posXAnt, posYAnt;
	//Direccion dir;
	void ataque();
	void perseguir();
	void rodear();
};

#endif