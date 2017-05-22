#ifndef Fuente_H
#define Fuente_H
#include "checkML.h"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

class Fuente
{
public:
	Fuente();
	Fuente(string const& nombArch, int size);
	~Fuente();

	void load(string const& nombArch, int size);
	void close();
	SDL_Surface* textSolid(string const& texto, SDL_Color color);

private:
	TTF_Font * pFont_;
};

#endif