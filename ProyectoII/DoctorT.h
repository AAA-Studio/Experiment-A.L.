#ifndef DoctorT_H
#define DoctorT_H
#include "checkML.h"
#include "Entidad.h"

class DoctorT : public Entidad
{
public:
	DoctorT(Juego*pJ, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto);
	~DoctorT();
	void draw(int x, int y)const;
	void update();
	inline void setRectAnim(){
		rectAn = { 0, 0, pJuego->getResources()->getTextura(JuegoSDL::TDoctorT)->getW() / 9, pJuego->getResources()->getTextura(JuegoSDL::TDoctorT)->getH() / 4};
	}

private: 
	//Animación
	SDL_Rect  rectAn;





};
#endif
