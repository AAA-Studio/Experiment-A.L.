#pragma once
#ifndef Menu_H
#define Menu_H
#include "checkML.h"
#include "Estado.h"


class Menu : public Estado
{
public:
	Menu(Juego * pJ);
	~Menu();
	virtual void draw()const;
	virtual void onInput(SDL_Event &e);

private:
	void initObjetos();

};

#endif
