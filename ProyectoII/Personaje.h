#ifndef Personaje_H
#define Personaje_H
#include "checkML.h"
#include "Entidad.h"
#include "Bala.h"
#include <list>



class Personaje : public Entidad
{
public:
	Personaje(Juego*pJ, int x, int y, Texturas_t color, Efectos_t efecto);//Constructora
	virtual ~Personaje();//Destructora

	virtual void update();//Actualiza el estado y devuelve false si el globo queda desinflado
	virtual void onInput();
	virtual void draw()const; //Para dibujar las balas

	void destruyeBala(Bala * bala);


	int getX(){ return posX; };
	int getY(){ return posY; };
	int getAngulo(){ return angulo; };

private:

	list <Bala*> balas;
	const float tiempoBala = 1000;
	float ultimaBala;
	int angulo;
	void disparo();
	void move(double x, double y);
};
#endif