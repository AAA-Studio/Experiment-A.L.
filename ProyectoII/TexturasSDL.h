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

	//Método para dibujar la textura en el rectángulo winRect
	void draw(SDL_Renderer* pRenderer, SDL_Rect const& winRect)const;

	//Métodos de consulta
	int getW() const { return ancho; };//Devuelve el ancho
	int getH() const{ return alto; };//Devuelve el alto

	void setRectText(int numFrame);


	//FUENTE
	void loadFromText(SDL_Renderer * pRender, string const& texto, SDL_Color color, Fuente fuente);

	void render(SDL_Renderer * pRenderer, int px, int py, string const& texto, Fuente fuente);

private:
	SDL_Texture * pTexture;//Puntero de la textura
	int alto, ancho;//Alto y ancho de la textura
	SDL_Rect texRect;

};
#endif // TexturasSDL_H
