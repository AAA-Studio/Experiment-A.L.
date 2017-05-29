#ifndef MundoVirtual_H
#define MundoVirtual_H
#include "checkML.h"
#include "EstadoJuego.h"
#include "EntidadJuego.h"
#include "Juego.h"

#include <list>

enum Mundo_t{ MReal, MOscuro };

class Personaje;
//Clase abstracta que hereda de la raiz EstadoJuego
class MundoVirtual : public EstadoJuego
{
public:

	//Colision
	virtual bool checkCollision(SDL_Rect a, SDL_Rect b) = 0;
	virtual EntidadJuego * compruebaColisionObjetos() = 0;

	//Destruccion objetos
	virtual void destruyeLlave(EntidadJuego * llave) = 0;
	virtual void destruyeBala(list <EntidadJuego*> &lista, list<EntidadJuego*>::iterator & it) = 0;
	virtual void destruyeArma() = 0;


	//Insertar objetos
	virtual void a�adeObjeto(EntidadJuego * obj) = 0;
	virtual void insertaBala(ListaBalas_t lista, EntidadJuego * bala) = 0;

	
	//Getters 
	virtual Juego* getPJ()const = 0;
	virtual Personaje * getPersonaje() = 0;
	virtual SDL_Rect getCamera() const = 0;
	virtual  int getNivel() const = 0;
	virtual int getIndiceMapa()const = 0;
	virtual bool getLLavesCogidas(int indice) const = 0;
	virtual  Mundo_t getMundo()const = 0;
	virtual list<EntidadJuego*> getListaBalas(ListaBalas_t lista) const = 0;
	virtual bool getPasoNivel()const = 0;
	virtual TexturasSDL getTextura() const = 0;
	virtual Fuente*  getFuente() const = 0;



	// Setters
	virtual  void setPasoNivel(bool pNivel) = 0;
	virtual void setCamera(int x, int y) = 0;
	virtual void setNivel(int i) = 0;
	virtual void setIndiceMapa(int i) = 0;
	virtual void setLlaveCogida(int indice) = 0;
	virtual void setMundo(Mundo_t m) = 0;
	virtual void setTextoArriba(bool text) = 0;
};

#endif