#pragma once
#ifndef Menu_H
#define Menu_H
#include "checkML.h"
#include "Estado.h"
#include "Mundo.h"


class Menu : public Estado
{
public:
	Menu(Juego * pJ);
	~Menu();
	void draw()const;

private:
	void initObjetos();

	static void goPlay(Juego * pj){
		Mundo * ePlay = new Mundo(pj);
		pj->changeState(ePlay);
	};
	static void goSalir(Juego * pj){
		pj->setSalir();
	}

};

#endif
