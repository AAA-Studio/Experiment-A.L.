#ifndef Musica_H
#define Musica_H

#include "checkML.h"
#include <SDL_mixer.h>
#include <string>

using namespace std;

class Musica
{
public:
	Musica();
	Musica(string const& nombArch);
	~Musica();
	void load(string const& nombArch);
	void play(int repetitions = -1);
	void pause();
	void close();

private:	
	Mix_Music * pMusic_;

};

class Efecto
{
public:
	Efecto();
	Efecto(string const& nombArch);
	~Efecto();
	void load(string const& nombArch);
	void play(int repetitions = -1);
	void pause();
	void close();

private:
	Mix_Chunk * pChunk_;

};

#endif