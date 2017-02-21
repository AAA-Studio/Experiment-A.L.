#ifndef GameOver_H
#define GameOver_H
#include "checkML.h"
#include "Estado.h"
#include "Menu.h"


class GameOver : public Estado
{
public:
	GameOver(Juego * pJ);
	~GameOver();

	virtual void draw() const;
private:
	void initObjetos();

	static void goMenu(Juego * pj){
		Menu * eMenu = new Menu(pj);
		pj->changeState(eMenu);
	};
};

#endif