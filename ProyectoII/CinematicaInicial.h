#ifndef _H_CinematicaInicial_H_
#define _H_CinematicaInicial_H_
#include "MundoVirtual.h"
#include "Mapa.h"
#include "Juego.h"
#include "Personaje.h"
#include "EntidadJuego.h"
#include "Enemigo.h"

class CinematicaInicial : public MundoVirtual
{
public:

	CinematicaInicial(Juego * pJ, string mapa);
	virtual ~CinematicaInicial();

	virtual void draw() const;
	virtual void onInput(SDL_Event &e);
	virtual void update();
	
	bool checkCollision(SDL_Rect a, SDL_Rect b){ return false; }
	inline void añadeObjeto(EntidadJuego * obj){}
	EntidadJuego * compruebaColisionObjetos(){ return nullptr; }
	virtual void destruyeLlave(EntidadJuego * llave){}
	void destruyeBala(list <EntidadJuego*> & lista, list<EntidadJuego*>::iterator & it){}
	void pildoraCogida(){}
	void setPulsado(){}
	void setPulsado2(){}
	void setCurapsj(){}
	void destruyeInterruptor(){}
	//------------------GETTERS---------------------
	inline Mapa* getMapa() const { return mapa; };
	inline Juego* getPJ() const{ return pJuego; };
	
	list<EntidadJuego*> getListaBalas(ListaBalas_t lista) const
	{
			return balasEnems;
	};
	void insertaBala(ListaBalas_t lista, EntidadJuego * bala){}

	

	void cambiaPosPSJ(int x, int y){
		psj->setPosChocando(x, y);
	}

	inline virtual SDL_Rect getCamera() const{ return camera; };

	virtual void setCamera(int x, int y){ camera.x = x; camera.y = y; };



	//Saber el nivel del mapa en el que estamos
	inline int getNivel() const { return nivel; };
	void setNivel(int i){
		nivel = i;
		indiceMapa += nivel;
	};

	//Mapa
	inline int getIndiceMapa()const { return indiceMapa; };
	inline void setIndiceMapa(int i){ indiceMapa = i; };

	//Llaves
	inline bool getLLavesCogidas(int indice) const{ return nullptr; }
	inline void setLlaveCogida(int indice) {}

	void destruyeArma(){};

	inline Personaje* getPersonaje(){ return psj; };
	inline Mundo_t getMundo()const{ return MReal; };
	inline bool getPasoNivel()const{ return true; };
	inline void setPasoNivel(bool pNivel){  };
	virtual void setMundo(Mundo_t m){};
	virtual bool checkColMapa(SDL_Rect enemigo){ return false; }

	inline void setTextoArriba(bool text){  };
	inline void setPuertaCerrada(bool puerta){};
	inline TexturasSDL* getTextura(){ return pJuego->getResources()->getTextura(0); };
	inline TexturasSDL * getTexturaBala(){ return pJuego->getResources()->getTextura(0); };
	inline TexturasSDL * getTexturaPCerrada(){ return pJuego->getResources()->getTextura(0); };
	inline Fuente*  getFuente()const{ return nullptr; };




private:
	//-------------------ATRIBUTOS---------------
	Juego * pJuego;
	Personaje * psj;
	vector <EntidadJuego*> objetos;
	list <EntidadJuego*> balasEnems;
	Mapa * mapa;
	bool pausa;
	SDL_Rect camera;

	int contador;
	bool moverI;
	bool dibuja;
	bool primeCinematica;

	int indiceMapa;
	int nivel;

	bool llavesCogidas[TAMAÑO_LLAVES];
	TexturasSDL textoPsj;
	bool comienzo;




	//-------------------METODOS-------------------
	void cargaObjetos();
	void initObjetos();
	void freeObjetos();
	
	void cinematicaInicial();
};

#endif
