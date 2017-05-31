#ifndef _H_BossFinal_H_
#define _H_BossFinal_H_
#include "Enemigo.h"

class BossFinal : public Enemigo
{
public:
	BossFinal(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto);
	virtual void update();
	~BossFinal();

protected:
	enum estados { ERecarga, EPersigue, EEmbiste };

	estados comportamiento;

	float timeR; //tiempo de recarga
	float timeE; //tiempo de recarga para embestir
	float timeA; //timepo antes de atacar
	float timeC; //tiempo de carga
	float passedTime;
	bool estoyCerca;
	int rangoDist; //distancia que le sumamos al rango para la embestida
	SDL_Rect dist; //para comprobar la distancia jugador enemigo
	int xPJ, yPJ; //donde guardamos las coordenadas del jugador para embestirle
	bool embistiendo; //para saber si estoy cargando contra el jugador y cuando he acabado
	bool llegado;
	const float tiempoBala = 1000;
	Uint32 ultimaBala;
	float angulo;


	void recargando();
	void embestir();
	virtual void perseguir();
	void cargarContraPJ();
	void disparo();


};

#endif
