#pragma once
#include "Menu.h"
class PantallaControles: public Menu
{
public:
	PantallaControles(Juego *pj);
	~PantallaControles();

virtual void draw()const;

private:
	void initObjetos();
};

