#ifndef Mundo_H
#define Mundo_H
#include "checkML.h"
#include "MundoVirtual.h"
#include "EntidadJuego.h"
#include "Juego.h"
#include "Armas.h"
#include <SDL.h>
#include "Mapa.h"
#include "Personaje.h"
#include "Pildoras.h"
#include "Interruptor.h"
#include "Enemigo.h"
#include <list>


using namespace std;




//Clase abstracta que hereda de la raiz ObjetoJuego e implementa utilidades para las subclases
class Mundo : public MundoVirtual
{
public:
	//Constructora
	Mundo(Juego * pJ, string mapa);

	//Destructorta
	virtual ~Mundo();

	//Interfaz
	virtual void draw() const;
	virtual void onInput(SDL_Event &e);
	virtual void update();

	//Colisiones
	bool checkCollision(SDL_Rect a, SDL_Rect b);//Lo necesito desde mapa
	EntidadJuego * compruebaColisionObjetos();//Se le llama desde personaje cuando pulsa la tecla 'E'

	//Destruccion objetos
	void destruyeBala(list <EntidadJuego*> & lista, list<EntidadJuego*>::iterator & it);
	void destruyeLlave(EntidadJuego * llave);
	void destruyeArma();
	virtual void destruyeInterruptor();
	//Insertar objetos
	inline void añadeObjeto(EntidadJuego * obj){ objetos.push_back(obj); };
	void insertaBala(ListaBalas_t lista, EntidadJuego * bala);
	void pildoraCogida();
	virtual void setPulsado();
	virtual void setPulsado2();


	//------------------GETTERS Y SETTER---------------------
	inline Mapa* getMapa() const { return mapa; };
	inline Juego* getPJ() const{ return pJuego; };
	inline Mundo_t getMundo()const{ return mundo; };
	virtual void setMundo(Mundo_t m){ mundo = m; };
	inline bool getPasoNivel()const{ return pasoNivel; };
	inline void setPasoNivel(bool pNivel){ pasoNivel = pNivel; };
	inline void setCurapsj(){ psj->sumaVida(3); }

	list<EntidadJuego*> getListaBalas(ListaBalas_t lista) const
	{
		if (lista == LBalasPersonaje)
			return balasPsj;
		else
			return balasEnems;
	};

	inline Personaje* getPersonaje(){ return psj; };

	//Camara
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
	inline bool getLLavesCogidas(int indice) const{ return llavesCogidas[indice]; };
	inline void setLlaveCogida(int indice) { llavesCogidas[indice] = !llavesCogidas[indice]; };

	//Fuente
	inline void setTextoArriba(bool text){ textArriba = text; };
	inline TexturasSDL *getTextura(){ return &textPlanta; };
	inline Fuente*  getFuente()const{ return font_; };
	//Metodo para escribir en una parte concreta de la ventana



	
private:

	//-------------------ATRIBUTOS---------------
	//Referencias a otros modulos
	Juego * pJuego;
	Mapa * mapa;

	//Mapa
	int indiceMapa;
	int nivel;

	//Mundo
	Mundo_t mundo;

	//Entidades
	Personaje * psj;

	list <Enemigo*> enemigos;
	list <EntidadJuego*> objetos;
	list <EntidadJuego*> llaves;
	list <Armas*> armas;
	list <Pildoras*> pildoras;
	list <Interruptor*> interruptores;
	SDL_Rect camera;

	//Balas
	list <EntidadJuego*> balasPsj;
	list <EntidadJuego*> balasEnems;
	Uint32 time;
	
	const Uint32 duracion = 500;
	bool balaDestruida;

	//Puertas
	bool llavesCogidas[TAMAÑO_LLAVES];
	bool pasoNivel;
	bool nivelCambiado;
	Uint32 alfo;

	bool colObjeto;
	bool textArriba;

	//Fuente
	Fuente* font_;
	TexturasSDL textCogerObj, textPlanta, textBalas;
	//bool abierto;
	//vector<bool> cerraduras;
	//vector<int> puertas;
	//bool pausa;

	//-------------------ATRIBUTOS---------------


	//-------------------METODOS-------------------
	//Objetos
	void initObjetos();
	void cargaObjetos();//Carga objetos de fichero
	void freeObjetos();

	//Colisiones
	void compruebaColisionPersonaje();//Colision con muros y puertas
	void colBalaEnemigo();
	void colBalaPersonaje();
	
	//-------------------METODOS-------------------
};

#endif
