#pragma once
#include "ObjetosJuego.h"
#include "Juego.h"
class Objetos : ObjetosJuego
{
public:
	Objetos(){};
	Objetos(int px, int py, Texturas_t text);
	virtual void dibujar();
	virtual void coger();
	virtual void soltar();
	~Objetos();

protected:
	bool visible; //se dibujan si son visibles 
	bool colision; //QUITAR, sustito del metodo de las colisiones de su propia clase
	Texturas_t textura; //textura del objeto
	SDL_Rect rectObjeto; //rectangulo del objeto
};

