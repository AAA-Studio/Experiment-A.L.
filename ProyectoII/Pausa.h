#ifndef Pausa_H
#define Pausa_H
#include "Estado.h"
#include "Menu.h"
#include "Mundo.h"


class Pausa : public Estado
{
public:
	Pausa(Juego * pJ);
	~Pausa();

	virtual void draw() const;
	virtual void onInput(SDL_Event &e);

private:
	void initObjetos();

	static void goPlay(Juego * pj){
		Mundo * ePlay = new Mundo(pj);
		pj->changeState(ePlay);
	};
	static void goMenu(Juego * pj){
		Menu * eMenu = new Menu(pj);
		pj->changeState(eMenu);
	};

};

#endif
