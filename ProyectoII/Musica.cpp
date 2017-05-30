#include "Musica.h"
#include "Error.h"

//Música
Musica::Musica() : pMusic_ (nullptr) {}

Musica::Musica(string const& nombArch) : pMusic_(nullptr), nombArchivo(nombArch) {
	load(nombArch);
}

Musica::~Musica(){	
	close();
	pMusic_ = nullptr;
}

void Musica::load(string const& nombArch){
	nombArchivo = nombArch;
	pMusic_ = Mix_LoadMUS(nombArch.c_str());//Cargamos el audio

	if (pMusic_ == nullptr)
	{
		ErrorSonido error("Error al cargar la música " + nombArch);
		throw error;
	}
}

void Musica::play(int repetitions){
	Mix_PlayMusic(pMusic_, repetitions);
}

void Musica::pause() {
	Mix_PauseMusic();
}

void Musica::close(){
	if (pMusic_ != nullptr) {
		Mix_FreeMusic(pMusic_);
		pMusic_ = nullptr;
	}
}
void Musica::closeAndLoad(){
	close();
	load(nombArchivo);
}


//Efecto
Efecto::Efecto() : pChunk_ (nullptr) {}

Efecto::Efecto(string const& nombArch) : pChunk_(nullptr) {
	load(nombArch);
}

Efecto::~Efecto(){
	close();
	pChunk_ = nullptr;
}

void Efecto::closeAndLoadEffect(){
	close();
	load(nombArchivo);
}
void Efecto::load(string const& nombArch){
	pChunk_ = Mix_LoadWAV(nombArch.c_str());//Cargamos el audio
	if (pChunk_ == nullptr)
	{
		ErrorSonido error("Error al cargar el efecto de sonido: " + nombArch);
		throw error;
	}
}

void Efecto::play(int repetitions){
	//repetitions = 1;
	if (pChunk_ != nullptr) 
		Mix_PlayChannel(-1, pChunk_, repetitions);
}

void Efecto::pause() {
	Mix_PauseMusic();
	//Mix_Pause(-1);
}

void Efecto::close(){
	if (pChunk_ != nullptr) {
		Mix_FreeChunk(pChunk_);
		pChunk_ = nullptr;
	}
}