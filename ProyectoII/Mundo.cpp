#include "Mundo.h"
#include "GameOver.h"
#include "Pausa.h"
#include <typeinfo>
#include "Personaje.h"
#include <iostream>
#include <SDL.h>
#include "Bala.h"
#include <fstream>
#include "Llave.h"

Mundo::Mundo(Juego * pJ) : Estado(pJ)
{
	pausa = false;
	objetos.resize(2);
	initObjetos();
	camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	setTiles();
	//pJuego->getMusica(MPlay)->play();
}


Mundo::~Mundo()
{
	//BORRAR TILES
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		if (tileMap[i] == NULL)
		{
			delete tileMap[i];
			tileMap[i] = NULL;
		}
	}

}


//Crea las texturas para los globos y todos los globos
void Mundo::initObjetos()
{
	int x = 0, y = 0;//Posiciones del globo
	x = rand() % (pJuego->getAncho() - 100);
	y = rand() % (pJuego->getAlto() - 100);
	// Personaje
	objetos[0] = new Personaje(pJuego, x, y, TJugador, ENull);
	objetos[1] = new Llave(pJuego, 400, 300, TLlave, ENull);
}



void Mundo::draw()const{

	//SDL_Rect fondoRect = { 0, 0, pJuego->getAncho(), pJuego->getAlto() };
	//pJuego->getTextura(TFondo)->draw(pJuego->getRender(), fondoRect);
	//Render level
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		tileMap[i]->render(camera);
	}

	//Dibujar objetos del juego
	Estado::draw();

	pJuego->getTextura(TFuente)->render(pJuego->getRender(), 0, 0, "Hola", pJuego->getFuente());

}


void Mundo::update(){
	Estado::update();
}

void Mundo::onInput(SDL_Event &e){
	
	//Declaramos el array con los estados de teclado
	const Uint8 * keyStatesActuales = SDL_GetKeyboardState(NULL);
	
	if (keyStatesActuales[SDL_SCANCODE_ESCAPE]){
			Pausa * pausa = new Pausa(pJuego);
			pJuego->goToPausa(pausa);
	}

	if (keyStatesActuales[SDL_SCANCODE_C]){ //coger objetos
		SDL_Rect rect1 = objetos[0]->getRect(); //rect del personaje
		SDL_Rect rect2; //rect del objeto
		bool coger = false; //para saber si se ha cogido o no el objeto
		bool colision = false; //para saber si hay colision entre un objeto y el personaje

		for (int i = objetos.size() - 1; i > 0 && (!coger); i--){//recorre los objetos con los que se puede colisionar
			SDL_Rect rect2 = objetos[i]->getRect(); //obtiene el rect del objeto
			//comprueba si hay colision entre el personaje y el objeto
			if (rect1.y + rect1.h >= rect2.y && rect1.y <= rect2.y + rect2.h && rect1.x + rect1.w >= rect2.x && rect1.x <= rect2.x + rect2.w)
				colision = true;
			else
				colision = false;
			//comprueba que son los tipos de objetos que se pueden coger
			if (/*colision && typeid(*objetos[i]) == typeid(Informe) && dynamic_cast<Informe*> (objetos[i])->visible
				|| */colision && typeid(*objetos[i]) == typeid(Llave) && dynamic_cast<Llave*> (objetos[i])->visible){
				//if (dynamic_cast<Informe*> (objetos[i])->visible){
				objetos[i]->coger();
				coger = true;
				//}
			}
			/*else if (colision && typeid(*objetos[i]) == typeid(Llave)){
			if (dynamic_cast<Llave*> (objetos[i])->visible){
			objetos[i]->coger();
			coger = true;
			}
			}*/
		}


	}

	//suelta el objeto en la posicion actual del jugador
	if (keyStatesActuales[SDL_SCANCODE_V]){
		double x = dynamic_cast<Personaje*> (objetos[0])->getX();
		double y = dynamic_cast<Personaje*> (objetos[0])->getY();
		objetos[1]->soltar(x, y);
	}

	objetos[0]->onInput();
	static_cast<Personaje*>(objetos[0])->setCamera(camera);

}


//Globo y premio
// Los objetos informarán al juego cuando causen baja
void Mundo::newBaja(EntidadJuego* po)
{
	/*if (typeid(*po) == typeid(Premio))
		dynamic_cast<Premio*> (po)->reiniciar();

	else
	{
		contGlobos--;
		if (contGlobos == 0)
		{
			GameOver *go = new GameOver(pJuego, puntosTotales);
			pJuego->changeState(go);
		}
	}*/
}

bool Mundo::checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	return !(bottomA <= topB || topA >= bottomB || rightA <= leftB || (leftA >= rightB));

}

bool Mundo::setTiles()
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map("..\\bmps\\lazy.map");

	//If the map couldn't be loaded
	if (!map.is_open())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		//Initialize the tiles
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
				tileMap[i] = new Tile(x, y, tileType,pJuego);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if (x >= LEVEL_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}

		//Close the file
		map.close();

		//If the map was loaded fine
		return tilesLoaded;
	}
}

bool Mundo::touchesWall(SDL_Rect box)
{
	//Go through the tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//If the tile is a wall type tile
		if ((tileMap[i]->getType() >= TILE_1)) //&& (tiles[i]->getType() <= TILE_3))

		{
			//If the collision box touches the wall tile
			if (checkCollision(box, tileMap[i]->getBox()))
			{
				return true;
			}
		}
	}

	//If no wall tiles were touched
	return false;

}
