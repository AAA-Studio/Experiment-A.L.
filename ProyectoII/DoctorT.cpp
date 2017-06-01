#include "DoctorT.h"


DoctorT::DoctorT(Juego*pJ, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto)
	: Entidad(pJ, x, y, w, h + 10, textura, efecto, ONull)
{
	rectAn = { 2 * pJuego->getResources()->getTextura(JuegoSDL::TDoctorT)->getW() / 9, 2 * pJuego->getResources()->getTextura(JuegoSDL::TDoctorT)->getH() / 4, pJuego->getResources()->getTextura(JuegoSDL::TDoctorT)->getW() / 9, pJuego->getResources()->getTextura(JuegoSDL::TDoctorT)->getH() / 4
};
}

void DoctorT:: update(){};
DoctorT::~DoctorT()
{
}
void DoctorT::draw(int x, int y)const{
	pJuego->getResources()->getTextura(textura)->draw(pJuego->getRender(), rect,x,y, &rectAn);//Dibujamos la textura

}
