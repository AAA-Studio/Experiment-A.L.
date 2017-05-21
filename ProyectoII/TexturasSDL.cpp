#include "TexturasSDL.h"
#include "Error.h"

TexturasSDL::TexturasSDL() : pTexture_(nullptr), texRect({ 0, 0, 0, 0 }){}

//Constructora imagenes
TexturasSDL::TexturasSDL(SDL_Renderer* renderer, string const& nombArch) :
pTexture_(nullptr), texRect({ 0, 0, 0, 0 }) {
	load(renderer, nombArch);
}

//Constructora fuentes
TexturasSDL::TexturasSDL(SDL_Renderer* renderer, string const& texto, const Fuente &font, const SDL_Color color) :
	pTexture_(nullptr), texRect({ 0, 0, 0, 0 }) {
	loadFromText(renderer, texto, color, font);
}

TexturasSDL::~TexturasSDL(){
	close();
}

void TexturasSDL::close() {
	if (pTexture_ != nullptr) {
		SDL_DestroyTexture(pTexture_); // delete current texture
		pTexture_ = nullptr;
		texRect = { 0, 0, 0, 0 };
	}
}

//Función para cargar el archivo
static SDL_Surface * loadArc(string nombreArchivo)
{
	SDL_Surface* pTempSurface = IMG_Load(nombreArchivo.c_str());
	return pTempSurface;
}

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
		close(); //Destruye textura anterior
		pTexture_ = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);//Crea la textura

		//Color key image
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		if (pTexture_ == nullptr)
		{
			ErrorImagen errorE("Error al crear la textura " + nombArch);
			throw errorE;
		}
		else
			texRect = { 0, 0, pTempSurface->w, pTempSurface->h };//Coge el ancho y el alto de la imagen 

		SDL_FreeSurface(pTempSurface);
	}
}

//Fuentes
void TexturasSDL::loadFromText(SDL_Renderer * pRender, string const& texto, SDL_Color color, Fuente fuente)
{
	SDL_Surface* pTempSurface = fuente.textSolid(texto, color);//Puntero a la imagen

	//Caso de error
	if (pTempSurface == nullptr)
	{
		ErrorFuente errorE("Error en la carga de la fuente: " + texto + " !SDL Error: " + IMG_GetError());
		throw errorE;
	}
	//Ha encontrado la imagen
	else
	{
		close(); //Destruye la imagen anterior
		pTexture_ = SDL_CreateTextureFromSurface(pRender, pTempSurface);//Crea la textura

		if (pTexture_ == nullptr)
		{
			ErrorFuente errorE("Error al crear la fuente");
			throw errorE;
		}
		else
			texRect = { 0, 0, pTempSurface->w, pTempSurface->h };
		
		SDL_FreeSurface(pTempSurface);
	}
}
//Método para dibujar la textura en el rectángulo winRect

//void TexturasSDL::draw(SDL_Renderer* pRenderer, SDL_Rect const& winRect, int x, int y, SDL_Rect* texRect)const

void TexturasSDL::draw(SDL_Renderer* pRenderer, SDL_Rect const& winRect,int x, int y, SDL_Rect const * texRect)const
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, winRect.w, winRect.h };

	//Render to screen
	SDL_RenderCopyEx(pRenderer, pTexture_, texRect, &renderQuad, 0, NULL, SDL_FLIP_NONE);
}

//Que primero genera la textura, a partir del texto y la fuente, y luego la muestra.
void TexturasSDL::renderFont(SDL_Renderer * pRenderer, int px, int py, string const& texto, Fuente fuente)
{
	SDL_Color color = { 255, 255, 255, 0 };
	loadFromText(pRenderer, texto, color, fuente);

	SDL_Rect winRect;// Rectangulo que ocupa en la ventana
	winRect = { px, py, texRect.w, texRect.h };
	draw(pRenderer, winRect,winRect.x,winRect.y,&texRect);
}

//TILE

void TexturasSDL::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(pTexture_, red, green, blue);
}

void TexturasSDL::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(pTexture_, blending);
}

void TexturasSDL::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(pTexture_, alpha);
}