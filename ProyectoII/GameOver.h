#ifndef GameOver_H
#define GameOver_H
#include "checkML.h"
#include "Menu.h"
#include "Juego.h"


class GameOver : public Menu
{
public:
	GameOver(Juego * pJ);
	~GameOver(){};

private:
	void initObjetos();

};

#endif