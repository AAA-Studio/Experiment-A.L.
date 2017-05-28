#include "Fuente.h"
#include "Error.h"

Fuente::Fuente() : pFont_(nullptr){}

Fuente::Fuente(string const& nombArch, int size) {
	load(nombArch, size);
}

Fuente::~Fuente(){
	close();
}

void Fuente::load(string const& nombArch, int size)
{
	pFont_ = TTF_OpenFont(nombArch.c_str(), size);
	if (pFont_ == nullptr)
	{
		ErrorFuente error("Error al cargar la fuente: " + nombArch);
		throw error;
	}
}

void Fuente::close()
{
	if (pFont_)
	{
		TTF_CloseFont(pFont_);
		pFont_ = nullptr;
	}
}

SDL_Surface* Fuente::textSolid(string const& texto, SDL_Color color) const
{
	if (pFont_) 
		return TTF_RenderText_Solid(pFont_, texto.c_str(), color);
	else 
		return nullptr;
}
