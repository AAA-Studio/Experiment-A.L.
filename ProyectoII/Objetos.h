#pragma once
#include "ObjetosJuego.h"
class Objetos : ObjetosJuego
{
public:
	Objetos(){};
	Objetos(int px, int py);
	virtual void dibujar();
	virtual void coger();
	virtual void soltar(int px, int py);
	~Objetos();

protected:
	bool visible; //se dibujan si son visibles 
	bool colision; //QUITAR, sustito del metodo de las colisiones de su propia clase
	int x; //posicion del objeto
	int y;
};

