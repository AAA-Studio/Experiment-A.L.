#ifndef Mundo_H
#define Mundo_H
#include "checkML.h"
#include "MundoVirtual.h"
#include "EntidadJuego.h"
#include "Juego.h"

#include <SDL.h>
#include "Mapa.h"
#include "Personaje.h"
#include <list>


using namespace std;

//Clase abstracta que hereda de la raiz ObjetoJuego e implementa utilidades para las subclases
class Mundo : public MundoVirtual
{
public:
	Mundo(Juego * pJ,string mapa);
	virtual ~Mundo();

	virtual void draw() const;
	virtual void onInput(SDL_Event &e);
	virtual void update();
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	inline void añadeObjeto(EntidadJuego * obj){ objetos.push_back(obj); };
	EntidadJuego * compruebaColisionObjetos();

	void destruyeLlave(EntidadJuego * llave);


	//------------------GETTERS---------------------
	inline Mapa* getMapa() const { return mapa; };
	inline Juego* getPJ() const{ return pJuego; };


private:
	//-------------------ATRIBUTOS---------------
	Juego * pJuego;
	Personaje * psj;
	vector <EntidadJuego*> objetos;
	list <EntidadJuego*> llaves;
	Mapa * mapa;
	bool pausa;
	const Uint32 duracion = 3000;
	Uint32 time;
	bool hayObj;
	//-------------------METODOS-------------------
	void cargaObjetos();
	void initObjetos();
	void freeObjetos();
};

#endif
