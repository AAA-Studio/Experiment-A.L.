
#ifndef PasoDeNivel_H
#define PasoDeNivel_H
#include "checkML.h"
#include "Menu.h"
#include "Juego.h"
#include "Musica.h"

class PasoDeNivel : public Menu
{
public:
	PasoDeNivel(Juego * pJ);
	~PasoDeNivel(){ /*pJuego->getResources()->getEfecto(JuegoSDL::Efectos_t::EPuerta)->close();*/ };
	virtual void update();
	virtual void draw() const;

private:
	void initObjetos();

	//Tiempo de estado
	const Uint32 duracion = 2000;
	Uint32 time;

	//Tiempo de Animación
	const Uint32 duracionAnim = 200;
	Uint32 timeAnim;//Contador para autodestruccion;

	SDL_Rect rect;
	SDL_Rect textRect;
}; 
#endif