#pragma once
#include "Menu.h"
class PantallaControles: public Menu
{
public:
	PantallaControles(Juego *pj);
	~PantallaControles();

virtual void draw()const;
virtual void update();
virtual void onInput(SDL_Event &e);

private:
	void initObjetos();
};

