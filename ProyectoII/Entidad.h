#ifndef Entidad_H
#define Entidad_H
#include "checkML.h"
#include "EntidadJuego.h"
#include "SDL.h"
#include "Mundo.h"

//Clase abstracta que hereda de la raiz ObjetoJuego e implementa utilidades para las subclases
class Entidad : public EntidadJuego
{
protected:

	virtual void draw() const;
	virtual bool onClick();
	//El update no se modifica

	Juego * pJuego;//Sustituye al puntero a la textura y al renderizador de la clase globo
	Texturas_t pTextura;
	Efectos_t sonido;

	int posX, posY, ancho, alto;
	SDL_Rect rect;//Rectángulo para cada textura

public:
	virtual SDL_Rect dameRect();//da el rectagulo necesario para las colisiones
	Entidad(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto);
	virtual ~Entidad();

private:
	bool dentro(int x, int y)const;//Comprueba si se ha hecho click en el objeto
};

#endif
