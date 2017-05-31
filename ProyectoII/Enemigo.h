#ifndef Enemigo_H
#define Enemigo_H
#include "checkML.h"
#include "Entidad.h"
#include <list>
#include "MundoVirtual.h"


class Enemigo : public Entidad
{
public:
	Enemigo(MundoVirtual*pJ, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto);
	~Enemigo();

	virtual void update();
	inline void restaVida() { vida--; };
	inline float getVida()const { return vida; };
	virtual void mover(int x, int y);

	virtual void setPosChocando(int x, int y);

	virtual inline int DamePosAntX(){ return posXAnt; };
	virtual inline int DamePosAntY(){ return posYAnt; };
	virtual void colision(bool chocando){ this->chocando = chocando; }
	virtual void draw(int x, int y)const;

protected:
	MundoVirtual* pMundo;
	int vida;
	int posXAnt, posYAnt;
	int velocidad; //velocidad de cada enemigo
	int x, y;
	int moveX, moveY;
	bool chocando; //si el personaje está chocando con algo
	bool ejeY, ejeX; //para saber que eje hay que comprobar

	bool atascadoX, atascadoY;
	SDL_Rect rectPJ; // rect del personaje

	virtual void pegar(float daño);
	virtual void perseguir();
	virtual void rodear();
	virtual void ataque(){}

	//anim
	SDL_Rect  rectAn;
	enum animar { derecha, izquierda, arriba, abajo };
	virtual void animacion(animar currentFrame);
	virtual void frames();
	int retardo;
	int enemigoDcha;
	int enemigoIzq;
	int enemigoArr;
	int sumaAnimX;
	int limiteX;
};

#endif