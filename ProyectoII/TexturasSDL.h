#ifndef TexturasSDL_H
#define TexturasSDL_H

#include "checkML.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>

#include "Fuente.h"

using namespace std;

class TexturasSDL
{
public:
	TexturasSDL();
	TexturasSDL(SDL_Renderer* renderer, string const& nombArch);//Constructora imagenes
	TexturasSDL(SDL_Renderer* renderer, string const& texto, const Fuente &font, const SDL_Color color);//Constructora fuentes

	~TexturasSDL();
	void close();

	//Métodos de consulta
	inline int getW() const { return texRect.w; };
	inline int getH() const{ return texRect.h; };

	void load(SDL_Renderer* pRenderer, string const& nombArch);//Imagenes
	void loadFromText(SDL_Renderer * pRender, string const& texto, SDL_Color color, const Fuente& fuente);//Fuentes

	//UTILIZAR VALORES POR DEFECTO PARA ANIMACIONES O ROTACIONES
	//void draw(SDL_Renderer* pRenderer, SDL_Rect const& winRect, int x, int y, SDL_Rect* texRect = NULL)const;
	void draw(SDL_Renderer* pRenderer, SDL_Rect const& winRect, int x, int y, SDL_Rect const * texRect)const;
	void renderFont(SDL_Renderer * pRenderer, int px, int py, Fuente fuente);


	//-----------TILE----------------------
	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);
	//----------------------------------------

private:
	SDL_Texture * pTexture_;//Puntero de la textura
	SDL_Rect texRect;

};
#endif // TexturasSDL_H
