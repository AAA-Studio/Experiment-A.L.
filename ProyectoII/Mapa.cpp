#include "Mapa.h"
#include "Mundo.h"
#include <fstream>

Mapa::Mapa(MundoVirtual *pM, string mapa) : pMundo(pM), nombreMapa(mapa)
{
	pJuego = pM->getPJ();
	cargarMapa();
	buscaSpawn();
	setCamera();
	Puerta1Abierta = false;
	encendido = false;
}

Mapa::~Mapa()
{
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		if (tileMap[i] == NULL)
		{
			delete tileMap[i];
			tileMap[i] = NULL;
		}
	}
}

bool Mapa::cargarMapa()
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map(nombreMapa);

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
				tileMap[i] = new Tile(x, y, tileType, pMundo->getPJ());
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

	}
	//If the map was loaded fine
	return tilesLoaded;

}

void  Mapa::buscaSpawn(){
	int i = 0;
	bool encontrado = false;
	int tipo = 0;

	if (pMundo->getNivel() == 0){
		x = 350;
		y = 350 + 640;
		encontrado = true;
		return;
	}

	//sale en el spawn gris
	else if (pMundo->getNivel() == -1)
		tipo = 185;
	//spawn rojo
	else if(pMundo->getNivel() == 1)
		tipo = 180;

	//spawn rosa
	else if(pMundo->getNivel() == 2)
		tipo = 191;

	//spawn morado
	else if(pMundo->getNivel() == -2)
		tipo = 184;
	
	//spawn azul oscuro
	else if(pMundo->getNivel() == 3)
		tipo = 190;

	//spawn pistacho
	else if(pMundo->getNivel() == -3)
		tipo = 188;

	//spawn marrón
	else if (pMundo->getNivel() == 4)
		tipo = 183;

	//spawn burdeos
	else if (pMundo->getNivel() == -4)
		tipo = 189;

	//spawn verde
	else if (pMundo->getNivel() == 5)
		tipo = 181;

	//spawn azul
	else if (pMundo->getNivel() == -5)
		tipo = 182;

	//spawn en espejo
	else if (pMundo->getIndiceMapa()<6 && pMundo->getNivel() == -6)
		tipo = 169;
	//------------------------------------------------------------------------------------//
	//                                      MUNDO OSCURO								  //
	//------------------------------------------------------------------------------------//
	//spawn espejo en oscuro
	else if (pMundo->getIndiceMapa()>5 && pMundo->getNivel() == 6)
		tipo = 364;
	//spawn azul en oscuro
	else if (pMundo->getIndiceMapa()>5 && pMundo->getNivel() == -5)
		tipo = 377;
	//spawn verde en oscuro
	else if (pMundo->getIndiceMapa()>5 && pMundo->getNivel() == 5)
		tipo = 376;
	//spawn rojo en oscuro
	else if (pMundo->getIndiceMapa()>5 && pMundo->getNivel() == 1)
		tipo = 375;
	//spawn gris en oscuro
	else if (pMundo->getIndiceMapa()>5 && pMundo->getNivel() == -1)
		tipo = 380;
	//spawn morado en oscuro
	else if (pMundo->getIndiceMapa()>5 && pMundo->getNivel() == -2)
		tipo = 379;
	//spawn rosa en oscuro
	else if (pMundo->getIndiceMapa()>5 && pMundo->getNivel() == 2)
		tipo = 386;
	//spawn burdeos en oscuro
	else if (pMundo->getIndiceMapa()>5 && pMundo->getNivel() == -4)
		tipo = 384;
	//spawn pistacho en oscuro
	else if (pMundo->getIndiceMapa()>5 && pMundo->getNivel() == -3)
		tipo = 383;
	//spawn azul oscuro en oscuro
	else if (pMundo->getIndiceMapa()>5 && pMundo->getNivel() == 3)
		tipo = 385;
	//spawn pistacho en oscuro
	else if (pMundo->getIndiceMapa()>5 && pMundo->getNivel() == 4)
		tipo = 378;

	while (!encontrado && i < TOTAL_TILES)
	{
		if (tileMap[i]->getType() == tipo){
			SDL_Rect rect = tileMap[i]->getBox();
			x = rect.x;
			y = rect.y;
			encontrado = true;
		}
		i++;
	}

	pMundo->cambiaPosPSJ(x, y);
	setCamera();
}

//Pone la cámara en el centro de cada nivel cuando se pasa de una sala a otra
void Mapa::setCamera()
{
	int ancho;
	if (pMundo->getIndiceMapa() < 6)
		ancho = 0;
	else 
		ancho = 1;
	pMundo->setCamera(800 * ancho, pMundo->getIndiceMapa() % 6 * 640);
}

bool Mapa::touchesDoor(SDL_Rect box, int& tipo)
{
	SDL_Rect felpudo;

	SDL_Rect camara = pMundo->getCamera();
	int j;
	int width = (camara.x + camara.w) / 32;
	int height = (camara.y + camara.h) / 32;
	 
	//Go through the tiles
	for (int i = camara.y / 32; i < height; ++i)
	{
		
		for (int j = camara.x / 32; j < width; j++)
		{
			int indice = j + i * (LEVEL_WIDTH / 32);
			//------------------------------------------------------------------------------------//
			//                                      MUNDO REAL									  //
			//------------------------------------------------------------------------------------//

			//If the tile is a wall type tile
			//-----------------------------------------------PUERTAS DE SUMAS----------------------------------
			//PUERTA ROJA
			if ((encendido)&&(tileMap[indice]->getType() == 150))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(-1);
					tipo = 150;
					buscaSpawn();
					return true;
				}
			}
			//PUERTA GRIS
			else if ((tileMap[indice]->getType() == 155))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 20;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(1);
					tipo = 155;
					buscaSpawn();
					return true;
				}

			}
			//PUERTA MORADA
			else if ((tileMap[indice]->getType() == 154))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 20;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(2);
					tipo = 154;
					buscaSpawn();
					return true;
				}

			}
			//PUERTA ROSA
			else if ((encendido)&&(tileMap[indice]->getType() == 140))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(-2);
					tipo = 140;
					buscaSpawn();
					return true;
				}

			}
			//PUERTA PISTACHO
			else if (pJuego->getPuerta(0) && (tileMap[indice]->getType() == 158))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(3);
					tipo = 158;
					buscaSpawn();
					return true;

				}

			}
			//PUERTA AZUL OSCURO
			else if ((tileMap[indice]->getType() == 165))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(-3);
					tipo = 165;
					buscaSpawn();
					return true;

				}

			}
			//PUERTA BURDEOS
			else if (false && (tileMap[indice]->getType() == 159))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(4);
					tipo = 159;
					buscaSpawn();
					return true;

				}

			}
			//PUERTA MARRÓN
			else if ((tileMap[indice]->getType() == 153))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(-4);
					tipo = 153;
					buscaSpawn();
					return true;

				}

			}
			//PUERTA AZUL
			else if (((pMundo->getLLavesCogidas(0) || Puerta1Abierta)) && (tileMap[indice]->getType() == 152))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 25;

				if (pMundo->checkCollision(box, felpudo)){

					if (pMundo->getLLavesCogidas(1) && !Puerta1Abierta){
						Puerta1Abierta = true;
						pMundo->setLlaveCogida(0);
					}
					else if (pMundo->getLLavesCogidas(0) && !Puerta1Abierta){
						Puerta1Abierta = true;
						pMundo->setLlaveCogida(0);
					}
					pMundo->setNivel(5);
					tipo = 152;
					buscaSpawn();
					return true;

				}

			}
			// PUERTA VERDE
			else if ((tileMap[indice]->getType() == 151))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(-5);
					tipo = 151;
					buscaSpawn();
					return true;

				}

			}

			// ESPEJO
			else if ((tileMap[indice]->getType() == 114))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(6);
					tipo = 114;
					buscaSpawn();
					return true;

				}

			}

			//------------------------------------------------------------------------------------//
			//                                      MUNDO OSCURO								  //
			//------------------------------------------------------------------------------------//

			//If the tile is a wall type tile
			//-----------------------------------------------PUERTAS DE SUMAS----------------------------------
			//PUERTA ROJA (OSCURO)
			else if ((tileMap[indice]->getType() == 345))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(-1);
					tipo = 345;
					buscaSpawn();
					return true;
				}
			}
			//PUERTA GRIS (OSCURO)
			else if ((tileMap[indice]->getType() == 350))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 20;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(1);
					tipo = 350;
					buscaSpawn();
					return true;
				}

			}
			//PUERTA MORADA (OSCURO)
			else if ((tileMap[indice]->getType() == 349))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 20;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(2);
					tipo = 349;
					buscaSpawn();
					return true;
				}

			}
			//PUERTA ROSA (OSCURO)
			else if ((tileMap[indice]->getType() == 335))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(-2);
					tipo = 335;
					buscaSpawn();
					return true;
				}

			}
			//PUERTA PISTACHO (OSCURO)
			else if ((tileMap[indice]->getType() == 353))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(3);
					tipo = 353;
					buscaSpawn();
					return true;

				}

			}
			//PUERTA AZUL OSCURO (OSCURO)
			else if ((tileMap[indice]->getType() == 360))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(-3);
					tipo = 360;
					buscaSpawn();
					return true;

				}

			}
			//PUERTA BURDEOS (OSCURO)
			else if ((tileMap[indice]->getType() == 354))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(4);
					tipo = 354;
					buscaSpawn();
					return true;

				}

			}
			//PUERTA MARRÓN
			else if ((tileMap[indice]->getType() == 348))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(-4);
					tipo = 348;
					buscaSpawn();
					return true;

				}

			}
			//PUERTA AZUL (OSCURO)
			else if ((tileMap[indice]->getType() == 347))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 25;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(5);
					tipo = 347;
					buscaSpawn();
					return true;

				}

			}
			// PUERTA VERDE (OSCURO)
			else if ((tileMap[indice]->getType() == 346))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(-5);
					tipo = 346;
					buscaSpawn();
					return true;

				}

			}

			// ESPEJO (OSCURO)
			else if ((tileMap[indice]->getType() == 309))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(-6);
					tipo = 309;
					buscaSpawn();
					return true;

				}

			}
		}
	}

	//If no wall tiles were touched
	return false;

}

bool Mapa::touchesWall(SDL_Rect box)
{
	bool salir = false;
	SDL_Rect camara = pMundo->getCamera();
	int i = camara.y / 32;
	int j;
	int width = (camara.x + camara.w) / 32;
	int height = (camara.y + camara.h) / 32;
	while (!salir && i < height)
	{
		j = camara.x / 32;
		while (!salir && j < width)
		{
			int indice = j + i * (LEVEL_WIDTH / 32);
			if ((tileMap[indice]->getType() != 0
				&& tileMap[indice]->getType() != 1
				&& tileMap[indice]->getType() != 2
				&& tileMap[indice]->getType() != 3
				&& tileMap[indice]->getType() != 16
				&& tileMap[indice]->getType() != 17
				&& tileMap[indice]->getType() != 18
				&& tileMap[indice]->getType() != 30
				&& tileMap[indice]->getType() != 31
				&& tileMap[indice]->getType() != 32
				&& tileMap[indice]->getType() != 33
				&& tileMap[indice]->getType() != 54
				&& tileMap[indice]->getType() != 55
				&& tileMap[indice]->getType() != 82
				&& tileMap[indice]->getType() != 114
				&& tileMap[indice]->getType() != 139
				&& tileMap[indice]->getType() != 140
				&& tileMap[indice]->getType() != 150
				&& tileMap[indice]->getType() != 151
				&& tileMap[indice]->getType() != 152
				&& tileMap[indice]->getType() != 153
				&& tileMap[indice]->getType() != 154
				&& tileMap[indice]->getType() != 155
				&& tileMap[indice]->getType() != 158
				&& tileMap[indice]->getType() != 159
				&& tileMap[indice]->getType() != 165
				&& tileMap[indice]->getType() != 169
				&& tileMap[indice]->getType() != 180
				&& tileMap[indice]->getType() != 181
				&& tileMap[indice]->getType() != 182
				&& tileMap[indice]->getType() != 183
				&& tileMap[indice]->getType() != 184
				&& tileMap[indice]->getType() != 185
				&& tileMap[indice]->getType() != 186
				&& tileMap[indice]->getType() != 187
				&& tileMap[indice]->getType() != 188
				&& tileMap[indice]->getType() != 189
				&& tileMap[indice]->getType() != 190
				&& tileMap[indice]->getType() != 191
				//------------------------------------------------------------------------------------//
				//                                      MUNDO OSCURO								  //
				//------------------------------------------------------------------------------------//

				&& tileMap[indice]->getType() != 195
				&& tileMap[indice]->getType() != 196
				&& tileMap[indice]->getType() != 197
				&& tileMap[indice]->getType() != 199
				&& tileMap[indice]->getType() != 200
				&& tileMap[indice]->getType() != 201
				&& tileMap[indice]->getType() != 202
				&& tileMap[indice]->getType() != 211
				&& tileMap[indice]->getType() != 212
				&& tileMap[indice]->getType() != 213
				&& tileMap[indice]->getType() != 214
				&& tileMap[indice]->getType() != 215
				&& tileMap[indice]->getType() != 216
				&& tileMap[indice]->getType() != 225
				&& tileMap[indice]->getType() != 226
				&& tileMap[indice]->getType() != 227
				&& tileMap[indice]->getType() != 228
				&& tileMap[indice]->getType() != 309
				&& tileMap[indice]->getType() != 334
				&& tileMap[indice]->getType() != 335
				&& tileMap[indice]->getType() != 345
				&& tileMap[indice]->getType() != 346
				&& tileMap[indice]->getType() != 347
				&& tileMap[indice]->getType() != 348
				&& tileMap[indice]->getType() != 349
				&& tileMap[indice]->getType() != 350
				&& tileMap[indice]->getType() != 353
				&& tileMap[indice]->getType() != 354
				&& tileMap[indice]->getType() != 360
				&& tileMap[indice]->getType() != 364
				&& tileMap[indice]->getType() != 375
				&& tileMap[indice]->getType() != 376
				&& tileMap[indice]->getType() != 377
				&& tileMap[indice]->getType() != 378
				&& tileMap[indice]->getType() != 379
				&& tileMap[indice]->getType() != 380
				&& tileMap[indice]->getType() != 382
				&& tileMap[indice]->getType() != 384
				&& tileMap[indice]->getType() != 383
				&& tileMap[indice]->getType() != 385
				&& tileMap[indice]->getType() != 386

				&& pMundo->checkCollision(box, tileMap[indice]->getBox())))
			{
				salir = true;
			}
			j++;
		}
		i++;

	}
	return salir;
}

void Mapa::draw()const{
	for (int i = 0; i < TOTAL_TILES; ++i)
		tileMap[i]->render(pMundo->getCamera());
}
