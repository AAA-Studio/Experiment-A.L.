#ifndef Personaje_H
#define Personaje_H
#include "checkML.h"
#include "Entidad.h"
#include "Bala.h"
#include <list>
#include <SDL.h>
#include <iostream>



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

	//Centers the camera over the dot
	void setCamera(SDL_Rect& camera);
	SDL_Rect getRectPsj(){ return rect; };

	void restaVida(){
		vida -= 10;
		std::cout << "me han pegao";
		static_cast <Mundo*> (pJuego->topEstado())->newBaja(this);
	}

private:
	
	list <Bala*> balas;
	const float tiempoBala = 1000;
	float ultimaBala;
	int angulo;
	bool balaDestruida;

	int vida;

	void disparo();
	void move(double x, double y);
};
#endif