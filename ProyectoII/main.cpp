#include <iostream>  // la consola: cin / cout
#include "Juego.h"
#include "Error.h"

//using namespace std;
//EN TEXTURASSDL, LAS ANIMACIONES HAY QUE MODIFICARLAS, EL SETRECKTEXT, SOLO ES APLICABLE A LA MARIPOSA
//CREAR ESTADOS ESTADO CON INPUT Y SIN INPUT QUE HEREDEN DE ESTADO
//EL INPUT NO VA BIEN

int main(int argc, char* args[]){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Detector de basura
	//_CrtDumpMemoryLeaks();// para que muestre la basura

	//Supuestamente libera los recursos si falla, no lo se
	try{
		Juego juego;
		juego.run();

	}
	catch (Error &e)
	{
		//Mostrar mensaje
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, e.mensaje().c_str(), "OK", nullptr);
		cin.ignore();
	}

	return 0;
}