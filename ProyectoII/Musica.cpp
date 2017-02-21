#include "Musica.h"
#include "Error.h"

//Música
Musica::Musica(){
	pMusic = nullptr;
}

Musica::~Musica(){	
	close();
	pMusic = nullptr;
}


void Musica::load(string const& nombArch){
	
	pMusic = Mix_LoadMUS(nombArch.c_str());//Cargamos el audio
	if (pMusic == nullptr)
	{
		ErrorSonido error("Error al cargar la música " + nombArch);
		throw error;

	}
}

void Musica::play(){
	Mix_PlayMusic(pMusic, -1);
}

void Musica::close(){
	Mix_FreeMusic(pMusic);
}


//Efecto
Efecto::Efecto(){
	pChunk = nullptr;
}

Efecto::~Efecto(){
	close();
	pChunk = nullptr;
}


void Efecto::load(string const& nombArch){

	pChunk = Mix_LoadWAV(nombArch.c_str());//Cargamos el audio
	if (pChunk == nullptr)
	{
		ErrorSonido error("Error al cargar el efecto de sonido: " + nombArch);
		throw error;

	}
}

void Efecto::play(){
	Mix_PlayChannel(-1, pChunk, 0);

}

void Efecto::close(){
	Mix_FreeChunk(pChunk);
}