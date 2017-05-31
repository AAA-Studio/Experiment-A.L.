#include "JuegoSDL.h"
#include <time.h>
#include "Error.h"


std::vector<std::string> JuegoSDL::imageFiles_{ "..\\bmps\\AL.png", "..\\bmps\\blood1.png", "..\\bmps\\hotelterror.png", "..\\bmps\\GameOver.png", "..\\bmps\\bala.png", "..\\bmps\\selft-time.png",
"..\\bmps\\manticora.png", "..\\bmps\\botonjugar.png",
"..\\bmps\\botonmenu.png", "..\\bmps\\botonsalir.png", "..\\bmps\\tilesdef.png", "..\\bmps\\llave.png",
"..\\bmps\\informe1.png", "..\\bmps\\Informe2.png", "..\\bmps\\Informe3.png", "..\\bmps\\Informe4.png", "..\\bmps\\Informe5.png", "..\\bmps\\Informe6.png", "..\\bmps\\Informe7.png",
"..\\bmps\\uno.png", "..\\bmps\\dos.png", "..\\bmps\\tres.png",
"..\\bmps\\cuatro.png", "..\\bmps\\cinco.png", "..\\bmps\\seis.png", "..\\bmps\\siete.png", "..\\bmps\\ocho.png", "..\\bmps\\nueve.png",
"..\\bmps\\cero.png", "..\\bmps\\teclado.png", "..\\bmps\\backButton.png", "..\\bmps\\pistola.png", "..\\bmps\\pildora.png", "..\\bmps\\BotePildoras.png", "..\\bmps\\interruptor.png", "..\\bmps\\Controles.png",
"..\\bmps\\Keypad.png", "..\\bmps\\enter.png", "..\\bmps\\negro.png", "..\\bmps\\enemigo1.png", "..\\bmps\\enemigo2.png", "..\\bmps\\enemigo3.png", "..\\bmps\\enemigo4.png",
"..\\bmps\\enemigo5.png", "..\\bmps\\invitacion.png" };

std::vector<std::string> JuegoSDL::fontFiles_{ 
	"..\\bmps\\selawk.ttf" };

std::vector<std::string> JuegoSDL::musicFiles_{ "..\\sounds\\mInicio.mp3",
"..\\sounds\\MundoReal.wav", "..\\sounds\\MundoOscuro.wav","..\\sounds\\gameOver.wav" };

std::vector<std::string> JuegoSDL::soundEffectFiles_{ "..\\sounds\\shootmp3.wav", "..\\sounds\\doormp3.mp3", "..\\sounds\\oscuro.mp3" ,
"..\\sounds\\cerrada.mp3", "..\\sounds\\correcto.wav", "..\\sounds\\pulsar.wav", "..\\sounds\\wrong.mp3", "..\\sounds\\objeto.wav" ,
"..\\sounds\\informe.wav", "..\\sounds\\llave abre puerta.wav", "..\\sounds\\monster1.wav","..\\sounds\\monster2.wav","..\\sounds\\storm.wav" };

JuegoSDL::JuegoSDL(std::string windowTitle, int width, int height) :
windowTitle_(windowTitle), width_(width), height_(height) {
	initSDL();
	initResources();
}

JuegoSDL::~JuegoSDL() {
	closeResources();//Hay que eliminarlos, hay elementos dinamicos
	closeSDL();
}

void JuegoSDL::initSDL() {
	//Inicializa y detecta si hay error
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		string errorSDL = SDL_GetError();
		Error errorE("SDL no se puede iniciar! SDL_Error: " + errorSDL);
		throw(errorE);
	}
	else
	{
		TTF_Init();

		// SDL Mixer (Music, Sound, etc)
		Mix_Init(MIX_INIT_FLAC | MIX_INIT_FLUIDSYNTH | MIX_INIT_MOD| MIX_INIT_MODPLUG | MIX_INIT_MP3 | MIX_INIT_OGG);

		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);

		// Create window .
		pWindow_ = SDL_CreateWindow(windowTitle_.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_SHOWN);

		//SDL_SetWindowFullscreen(pWin, SDL_WINDOW_FULLSCREEN);

		//Caso de error en el que no se crea la ventana
		if (pWindow_ == nullptr)
		{
			string errorSDL = SDL_GetError();
			Error errorE("La ventana no pudo crearse!SDL_Error: " + errorSDL);
			throw(errorE);
		}
		else
		{
			//Obtenemos la superficie de la ventana:
			pRenderer_ = SDL_CreateRenderer(pWindow_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (pRenderer_ == nullptr)
			{
				string errorSDL = SDL_GetError();
				Error errorE("El renderer no pudo crearse! SDL_Error: " + errorSDL);
				throw(errorE);
			}

			//Ponemos color al fondo de la ventana
			colorWin = { 0, 0, 0, 255 };
			SDL_SetRenderDrawColor(pRenderer_, colorWin.r, colorWin.g, colorWin.b, colorWin.a); 
			SDL_RenderClear(pRenderer_);
			SDL_RenderPresent(pRenderer_);

		}
	}

	//Genera la semilla aleatoria para numeros aleatorios
	srand(time(NULL));

}

void JuegoSDL::closeSDL() {

	SDL_DestroyRenderer(pRenderer_);
	pRenderer_ = nullptr;

	SDL_DestroyWindow(pWindow_);
	pWindow_ = nullptr;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();

	SDL_Quit();
}

void JuegoSDL::initResources() {
	pResources_ = new RecursosSDL(this);
	pResources_->setTextures(imageFiles_);
	pResources_->setFonts(fontFiles_);
	pResources_->setMusic(musicFiles_);
	pResources_->setSoundEffects(soundEffectFiles_);
}

void JuegoSDL::closeResources() {
	delete pResources_;
}