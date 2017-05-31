#ifndef JUEGOSDL_H_
#define JUEGOSDL_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "RecursosSDL.h"


class JuegoSDL {
public:
	//Se definen los enums de todos los recursos

	enum  Texturas_t{ TJugador, TBlood, TFondo, TBala, TFuego, TLeon, TPlay, TMenu, TExit, TTilemap, TLlave, TInforme1, TInforme2, TUno, TDos, TTres, TCuatro, TCinco, TSeis, TSiete, TOcho, TNueve, TCero, TTeclado, TVolver, TPistola, TControles, TKeypad, TEnter, TNegro, TEnemigo, TEnemigo2, TEnemigo3, TEnemigo4, TEnemigo5,/*TFondoMenu,*/ TFuente, Texturas_t_SIZE };
	static std::vector<std::string> imageFiles_;

	enum Fuentes_t {
		FNormal
	};
	static std::vector<std::string> JuegoSDL::fontFiles_;

	enum  Musica_t{ MInicio,MReal,MOscuro, Musica_t_SIZE };
	static std::vector<std::string> musicFiles_;

	enum  Efectos_t{ EBala, EPuerta, EEspejo, ECerrada, ECorrecto, EPulsar, EIncorrecto, EObjeto, EInforme, ELlave, ENull, Efectos_t_SIZE };
	static std::vector<std::string> soundEffectFiles_;

public:
	JuegoSDL(std::string windowTitle_, int width, int height);
	virtual ~JuegoSDL();

	inline SDL_Window* getWindow() const { return pWindow_;}; // returns a pointer to the SDL window
	inline SDL_Renderer * getRender() const{ return pRenderer_; };
	inline int getWindowWidth() const{ return width_; };
	inline int getWindowHeight() const 	{ return height_; };
	inline const RecursosSDL* getResources() const {return pResources_;}; // returns a pointer to the resources

	// abstract methods to be implemented by subclasses
	virtual void run() = 0; // start the game
	//virtual void stop() = 0;  // stop the game

private:
	void initSDL(); // initialize SDL (ttf, mixer, image, create window and renderer, etc)
	void closeSDL(); // close all SDL resources
	void initResources(); // initialize the SDLResources object with the data at the top of this file
	void closeResources(); // close the  SDLResources object (frees all memory)

protected:
	SDL_Window* pWindow_; // the window
	SDL_Renderer* pRenderer_;  // the renderer
	RecursosSDL* pResources_; // resource (textures, font, music, etc)

	std::string windowTitle_; // window title
	int width_; // window width
	int height_; // window height

	SDL_Color colorWin;//Color de la ventana
};

#endif /* SDLGAME_H_ */

