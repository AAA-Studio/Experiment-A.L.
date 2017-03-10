#ifndef GameOver_H
#define GameOver_H
#include "checkML.h"
#include "Estado.h"


class GameOver : public Estado
{
public:
	GameOver(Juego * pJ);
	~GameOver(){};

	virtual void draw() const;
	virtual void onInput(SDL_Event &e);
private:
	void initObjetos();

};

#endif