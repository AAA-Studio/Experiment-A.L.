#include "TexturasSDL.h"
#include "Error.h"

//Constructora
TexturasSDL::TexturasSDL()
{
	pTexture = nullptr;//Puntero de la textura
}

//Destructora
TexturasSDL::~TexturasSDL()
{
	SDL_DestroyTexture(pTexture);
	pTexture = nullptr;
}

//Función para cargar el archivo
static SDL_Surface * loadArc(string nombreArchivo)
{
	SDL_Surface* pTempSurface = nullptr;
	pTempSurface = IMG_Load(nombreArchivo.c_str());

	return pTempSurface;
}

//Método para cargar una textura y aplicar la transparencia, detecta caso de error y devuelve false
//Una vez cargado el archivo, y antes de generar la textura, pone el color colKey transparente
void TexturasSDL::load(SDL_Renderer* pRenderer, string const& nombArch){

	SDL_Surface* pTempSurface = loadArc(nombArch);//Puntero a la imagen

	//Caso de error
	if (pTempSurface == nullptr)
	{
		ErrorImagen errorE("Error en la carga de la textura " + nombArch + "!SDL Error: " + IMG_GetError());
		throw errorE;
	}
	//Ha encontrado la imagen
	else
	{
		//Color key image
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Coge el ancho y el alto de la imagen 
		texRect = { 0, 0, pTempSurface->w, pTempSurface->h };

		pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);//Crea la textura
		if (pTexture == nullptr)
		{
			ErrorImagen errorE("Error al crear la textura " + nombArch);
			throw errorE;
		}

		SDL_FreeSurface(pTempSurface);
	}

}

//Método para dibujar la textura en el rectángulo winRect
void TexturasSDL::draw(SDL_Renderer* pRenderer, SDL_Rect const& winRect, SDL_Rect const * texRect)const
{
	SDL_RenderCopyEx(pRenderer, pTexture, texRect, &winRect,0,NULL,SDL_FLIP_NONE);
}

void TexturasSDL::setRectText(int numFrame){
	// 7 no vale, tiene que ser especifico de cada personaje
	texRect = { texRect.w / 7 * (numFrame % 7), 0, texRect.w / 7, texRect.h };//Posición actual delJugador
}

//Fuente
void TexturasSDL::loadFromText(SDL_Renderer * pRender, string const& texto, SDL_Color color, Fuente fuente)
{
	SDL_Surface* pTempSurface = fuente.textSolid(texto, color);//Puntero a la imagen

	//Caso de error
	if (pTempSurface == nullptr)
	{
		string errorSDL = IMG_GetError();
		ErrorFuente errorE("Error en la carga de la textura FUENTE, !SDL Error: " + errorSDL+ "");
		throw errorE;
	}
	//Ha encontrado la imagen
	else
	{
		texRect = { 0, 0, pTempSurface->w, pTempSurface->h };

		SDL_DestroyTexture(pTexture);
		pTexture = SDL_CreateTextureFromSurface(pRender, pTempSurface);//Crea la textura

		if (pTexture == nullptr)
		{
			ErrorFuente errorE("Error al crear la fuente");
			throw errorE;
		}
		SDL_FreeSurface(pTempSurface);
	
	}

}

//Que primero genera la textura, a partir del texto y la fuente, y luego la muestra.
void TexturasSDL::render(SDL_Renderer * pRenderer, int px, int py, string const& texto, Fuente fuente)
{
	SDL_Color color = { 255, 255, 255, 0 };
	loadFromText(pRenderer, texto, color, fuente);

	SDL_Rect winRect;// Rectangulo que ocupa en la ventana
	winRect = { px, py, texRect.w, texRect.h };
	draw(pRenderer, winRect);
}

//TILE

void TexturasSDL::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(pTexture, red, green, blue);
}

void TexturasSDL::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(pTexture, blending);
}

void TexturasSDL::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(pTexture, alpha);
}