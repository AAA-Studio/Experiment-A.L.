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
	//Constructora
	TexturasSDL();
	//Destructora
	~TexturasSDL();

	//Método para cargar una textura y aplicar la transparencia, detecta caso de error y devuelve false
	//Una vez cargado el archivo, y antes de generar la textura, pone el color colKey transparente
	void load(SDL_Renderer* pRenderer, string const& nombArch);//Es para el juego

	//UTILIZAR VALORES POR DEFECTO PARA ANIMACIONES O ROTACIONES
	//Método para dibujar la textura en el rectángulo winRect



	void draw(SDL_Renderer* pRenderer, SDL_Rect const& winRect, int x, int y, SDL_Rect* texRect = NULL)const;

	//void draw(SDL_Renderer* pRenderer, SDL_Rect const& winRect, SDL_Rect const * texRect = NULL)const;




	//Métodos de consulta
	inline int getW() const { return texRect.w; };//Devuelve el ancho
	inline int getH() const{ return texRect.h; };//Devuelve el alto

	//Animacion
	void setRectText(int numFrame);


	//---------------FUENTE-------------------------

	void loadFromText(SDL_Renderer * pRender, string const& texto, SDL_Color color, Fuente fuente);

	void render(SDL_Renderer * pRenderer, int px, int py, string const& texto, Fuente fuente);

	//----------------------------------------------------


	//-----------TILE----------------------
	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);
	//----------------------------------------


private:
	SDL_Texture * pTexture;//Puntero de la textura
	SDL_Rect texRect;

};
#endif // TexturasSDL_H
