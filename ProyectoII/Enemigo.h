#ifndef Enemigo_H
#define Enemigo_H
#include "checkML.h"
#include "Entidad.h"
#include "PersonajeVirtual.h"
#include <list>


class Enemigo : public Entidad, PersonajeVirtual
{
public:
	Enemigo(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto);
	~Enemigo();
	virtual void update();
	void destruyeBala(EntidadJuego * bala);
	inline void restaVida() { vida--; };
	inline int getVida()const { return vida; };
	virtual void draw()const; //Para dibujar las balas

private:

	void disparo();
	list <EntidadJuego*> balas;
	int vida;
	const float tiempoBala = 1000;
	Uint32 ultimaBala;
	bool balaDestruida;
	int angulo;

};

#endif