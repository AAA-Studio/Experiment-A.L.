#ifndef Musica_H
#define Musica_H
#include "checkML.h"
#include <SDL_mixer.h>
#include <string>


using namespace std;
//Clase Musica
class Musica
{
public:
	Musica();
	~Musica();
	void load(string const& nombArch);
	void play();
	void close();

private:	
	Mix_Music * pMusic;

};

//Clase Efecto
class Efecto
{
public:
	Efecto();
	~Efecto();
	void load(string const& nombArch);
	void play();
	void close();

private:
	Mix_Chunk * pChunk;

};
#endif