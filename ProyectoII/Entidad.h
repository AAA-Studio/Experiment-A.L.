#ifndef Entidad_H
#define Entidad_H
#include "checkML.h"
#include "EntidadJuego.h"
#include "SDL.h"
#include "Juego.h"
//Clase abstracta que hereda de la raiz ObjetoJuego e implementa utilidades para las subclases
class Entidad : virtual public EntidadJuego
{
public:

	Entidad(Juego*pJ, double x, double y, double w, double h, JuegoSDL::Texturas_t tex, JuegoSDL::Efectos_t efecto, Objetos_t tipo);

	virtual ~Entidad();

	virtual void draw(int x, int y) const;
	virtual void onInput() {};
	virtual void update() {};

	virtual inline SDL_Rect getRect()const{ return rect; };
	virtual inline void setRect(SDL_Rect r) { rect = r; };
	virtual inline Objetos_t getType() const  { return type; };

	virtual void setVisible(bool visible);
	virtual void move(int x, int y);
protected:

	Juego * pJuego;//Sustituye al puntero a la textura y al renderizador de la clase globo
	JuegoSDL::Texturas_t textura;
	JuegoSDL::Efectos_t sonido;
	Objetos_t type;

	SDL_Rect rect;//Rectángulo para cada textura

	bool visible;
};

#endif
