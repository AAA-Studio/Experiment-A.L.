
#ifndef MenuInicio_H
#define MenuInicio_H
#include "checkML.h"
#include "Menu.h"
#include "Juego.h"
#include "Musica.h"


class MenuInicio : public Menu
{
public:
	MenuInicio(Juego * pJ);
	~MenuInicio(){ pJuego->getMusica(MusicaInicio)->close(); };
	virtual void draw()const;

private:
	void initObjetos();

};

#endif
