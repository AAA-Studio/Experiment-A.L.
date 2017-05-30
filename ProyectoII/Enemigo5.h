#ifndef _H_Enemigo5_H_
#define _H_Enemigo5_H_

#include "Entidad.h"
#include "MundoVirtual.h"

class Enemigo5 : public Entidad
{
public:
	Enemigo5(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto);
	~Enemigo5();

	// Lo que tiene que hacer el enemigo 5 es embestir al jugador, desde la posicion donde este el enemigo, 
	// guarda la posicion del personaje y embiste hasta llegar a la posicion de personaje,
	// depende de la distancia que haya recorrido en la embestida te empuja
	// Si hay un obstaculo entre enemigo y personaje, no hay embestida
	// Cuando ha realizado la embestida, se mueve, se coloca para embestir otra vez y procede.


	// Implementacion
	// El jugador tendra dos circunferencias a su alrededor, una pequeña y otra grande.
	// Si el enemigo esta dentro de la grande pero fuera de la pequeña antes de la embestida,
	// cuando carga, desplaza al jugador.
	// Si el enemigo esta dentro de la grande pero fuera de la pequeña, carga sin desplazar.
	// Si el enemigo esta dentro de la pequeña, no embiste y se aleja para proceder con la embestida

	virtual void update();
	inline void restaVida() { vida--; };
	inline float getVida()const { return vida; }
	void movimiento(SDL_Rect target);
	void setPosChocando(int x, int y);
	

protected:

	enum dirY{ up, down, no };
	enum dirX{ izq, drcha, none };
	SDL_Rect rectPJ; // rect del personaje
	MundoVirtual* pMundo;
	int vida;
	char xCol, yCol;
	bool chocando, estaEnEmbestida, estabaEmbistiendo;

	//Direccion dir;
	
	bool EstaEnArea(float distancia);

	dirY m_dirY;
	dirX m_dirX;

	SDL_Rect rectAntesEmbestida;
};
#endif

