#include "Fuente.h"
#include "Error.h"

Fuente::Fuente()
{
	pFont = nullptr;
}

Fuente::~Fuente()
{
	pFont = nullptr;
}

void Fuente::load(string const& nombArch)
{
	pFont = TTF_OpenFont(nombArch.c_str(), 28);
	if (pFont == nullptr)
	{
		ErrorFuente error("Error al cargar la fuente: " + nombArch);
		throw error;
	}
}

void Fuente::close()
{
	TTF_CloseFont(pFont);
}

SDL_Surface* Fuente::textSolid(string const& texto, SDL_Color color)
{
	return TTF_RenderText_Solid(pFont, texto.c_str(), color);
}
