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
	nivel = 0;
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

	if (pJuego->getNivel() == 0){
		x = 350;
		y = 350 + 640;
		encontrado = true;
		return;
	}

	//sale en el spawn gris
	else if (pJuego->getNivel() == -1)
		tipo = 185;
	//spawn rojo
	else if(pJuego->getNivel() == 1)
		tipo = 180;

	//spawn rosa
	else if(pJuego->getNivel() == 2)
		tipo = 191;

	//spawn morado
	else if(pJuego->getNivel() == -2)
		tipo = 184;
	
	//spawn azul oscuro
	else if(pJuego->getNivel() == 3)
		tipo = 190;

	//spawn pistacho
	else if(pJuego->getNivel() == -3)
		tipo = 188;

	//spawn marr�n
	else if (pJuego->getNivel() == 4)
		tipo = 183;

	//spawn burdeos
	else if (pJuego->getNivel() == -4)
		tipo = 189;

	//spawn verde
	else if (pJuego->getNivel() == 5)
		tipo = 181;

	//spawn azul
	else if (pJuego->getNivel() == -5)
		tipo = 182;

	//spawn en espejo
	else if (pJuego->indiceMapas<6 && pJuego->getNivel() == -6)
		tipo = 169;
	//------------------------------------------------------------------------------------//
	//                                      MUNDO OSCURO								  //
	//------------------------------------------------------------------------------------//
	//spawn espejo en oscuro
	else if (pJuego->indiceMapas>5 && pJuego->getNivel() == 6)
		tipo = 364;
	//spawn azul en oscuro
	else if (pJuego->indiceMapas>5 && pJuego->getNivel() == -5)
		tipo = 377;
	//spawn verde en oscuro
	else if (pJuego->indiceMapas>5 && pJuego->getNivel() == 5)
		tipo = 376;
	//spawn rojo en oscuro
	else if (pJuego->indiceMapas>5 && pJuego->getNivel() == 1)
		tipo = 375;
	//spawn gris en oscuro
	else if (pJuego->indiceMapas>5 && pJuego->getNivel() == -1)
		tipo = 380;
	//spawn morado en oscuro
	else if (pJuego->indiceMapas>5 && pJuego->getNivel() == -2)
		tipo = 379;
	//spawn rosa en oscuro
	else if (pJuego->indiceMapas>5 && pJuego->getNivel() == 2)
		tipo = 386;
	//spawn burdeos en oscuro
	else if (pJuego->indiceMapas>5 && pJuego->getNivel() == -4)
		tipo = 384;
	//spawn pistacho en oscuro
	else if (pJuego->indiceMapas>5 && pJuego->getNivel() == -3)
		tipo = 383;
	//spawn azul oscuro en oscuro
	else if (pJuego->indiceMapas>5 && pJuego->getNivel() == 3)
		tipo = 385;
	//spawn pistacho en oscuro
	else if (pJuego->indiceMapas>5 && pJuego->getNivel() == 4)
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

//Pone la c�mara en el centro de cada nivel cuando se pasa de una sala a otra
void Mapa::setCamera()
{
	int ancho;
	if (pJuego->indiceMapas < 6)
		ancho = 0;
	else 
		ancho = 1;
	pMundo->setCamera(800 * ancho, pJuego->indiceMapas % 6 * 640);
}

bool Mapa::touchesDoor(SDL_Rect box, int& tipo)
{
	SDL_Rect felpudo;
	 
	//Go through the tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//------------------------------------------------------------------------------------//
		//                                      MUNDO REAL									  //
		//------------------------------------------------------------------------------------//

		//If the tile is a wall type tile
		//-----------------------------------------------PUERTAS DE SUMAS----------------------------------
		//PUERTA ROJA
			if ((tileMap[i]->getType() == 150))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;
					
					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(-1);
						tipo = 150;
						buscaSpawn();
						return true;
					}
				}
					//PUERTA GRIS
			else if ((tileMap[i]->getType() == 155))
					{
						felpudo = tileMap[i]->getBox();
						felpudo.x = felpudo.x + 10;
						felpudo.y = felpudo.y + 25;
						felpudo.h = felpudo.h - 20;
						felpudo.w = felpudo.w - 20;

						if (pMundo->checkCollision(box, felpudo)){
							pJuego->setNivel(1);
							tipo = 155;
							buscaSpawn();
							return true;
						}

					}
				//PUERTA MORADA
			else if ((tileMap[i]->getType() == 154))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 20;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(2);
						tipo = 154;
						buscaSpawn();
						return true;
					}

				}
				//PUERTA ROSA
			else if ((tileMap[i]->getType() == 140))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(-2);
						tipo = 140;
						buscaSpawn();
						return true;
					}

				}
				//PUERTA PISTACHO
			else if (pJuego->getPuerta(0) && (tileMap[i]->getType() == 158))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(3);
						tipo = 158;
						buscaSpawn();
						return true;

					}

				}
				//PUERTA AZUL OSCURO
			else if ((tileMap[i]->getType() == 165))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(-3);
						tipo = 165;
						buscaSpawn();
						return true;

					}

				}
				//PUERTA BURDEOS
			else if (false && (tileMap[i]->getType() == 159))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(4);
						tipo = 159;
						buscaSpawn();
						return true;

					}

				}
				//PUERTA MARR�N
			else if ((tileMap[i]->getType() == 153))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(-4);
						tipo = 153;
						buscaSpawn();
						return true;

					}

				}
				//PUERTA AZUL
			else if (((pJuego->getLLavesCogidas(0) || Puerta1Abierta)) && (tileMap[i]->getType() == 152))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 25;
					
					if (pMundo->checkCollision(box, felpudo)){
						
						if (pJuego->getLLavesCogidas(1) && !Puerta1Abierta){
							Puerta1Abierta = true;
							pJuego->setLlaveCogida(0);
						}
						else if (pJuego->getLLavesCogidas(0) && !Puerta1Abierta){
							Puerta1Abierta = true;
							pJuego->setLlaveCogida(0);
						}
						pJuego->setNivel(5);
						tipo = 152;
						buscaSpawn();
						return true;

					}

				}
				// PUERTA VERDE
			else if ((tileMap[i]->getType() == 151))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(-5);
						tipo = 151;
						buscaSpawn();
						return true;

					}

				}

				// ESPEJO
			else if ((tileMap[i]->getType() == 114))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(6);
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
			else if ((tileMap[i]->getType() == 345))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(-1);
						tipo = 345;
						buscaSpawn();
						return true;
					}
				}
				//PUERTA GRIS (OSCURO)
			else if ((tileMap[i]->getType() == 350))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 20;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(1);
						tipo = 350;
						buscaSpawn();
						return true;
					}

				}
				//PUERTA MORADA (OSCURO)
			else if ((tileMap[i]->getType() == 349))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 20;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(2);
						tipo = 349;
						buscaSpawn();
						return true;
					}

				}
				//PUERTA ROSA (OSCURO)
			else if ((tileMap[i]->getType() == 335))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(-2);
						tipo = 335;
						buscaSpawn();
						return true;
					}

				}
				//PUERTA PISTACHO (OSCURO)
			else if ((tileMap[i]->getType() == 353))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(3);
						tipo = 353;
						buscaSpawn();
						return true;

					}

				}
				//PUERTA AZUL OSCURO (OSCURO)
			else if ((tileMap[i]->getType() == 360))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(-3);
						tipo = 360;
						buscaSpawn();
						return true;

					}

				}
				//PUERTA BURDEOS (OSCURO)
			else if ((tileMap[i]->getType() == 354))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(4);
						tipo = 354;
						buscaSpawn();
						return true;

					}

				}
				//PUERTA MARR�N
			else if ((tileMap[i]->getType() == 348))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(-4);
						tipo = 348;
						buscaSpawn();
						return true;

					}

				}
				//PUERTA AZUL (OSCURO)
			else if ((tileMap[i]->getType() == 347))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 25;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(5);
						tipo = 347;
						buscaSpawn();
						return true;

					}

				}
				// PUERTA VERDE (OSCURO)
			else if ((tileMap[i]->getType() == 346))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(-5);
						tipo = 346;
						buscaSpawn();
						return true;

					}

				}

				// ESPEJO (OSCURO)
			else if ((tileMap[i]->getType() == 309))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;
					
					if (pMundo->checkCollision(box, felpudo)){
						pJuego->setNivel(-6);
						tipo = 309;
						buscaSpawn();
						return true;

					}

				}
	}

	//If no wall tiles were touched
	return false;

}

bool Mapa::touchesWall(SDL_Rect box)
{
	bool aux = false;
	int i = 0;
	while (!aux && i < TOTAL_TILES)
	{
		if ((tileMap[i]->getType() != 0
			&& tileMap[i]->getType() != 1
			&& tileMap[i]->getType() != 2
			&& tileMap[i]->getType() != 3
			&& tileMap[i]->getType() != 16
			&& tileMap[i]->getType() != 17
			&& tileMap[i]->getType() != 18
			&& tileMap[i]->getType() != 30
			&& tileMap[i]->getType() != 31
			&& tileMap[i]->getType() != 32
			&& tileMap[i]->getType() != 33
			&& tileMap[i]->getType() != 54
			&& tileMap[i]->getType() != 55
			&& tileMap[i]->getType() != 82
			&& tileMap[i]->getType() != 114
			&& tileMap[i]->getType() != 139
			&& tileMap[i]->getType() != 140
			&& tileMap[i]->getType() != 150
			&& tileMap[i]->getType() != 151
			&& tileMap[i]->getType() != 152
			&& tileMap[i]->getType() != 153
			&& tileMap[i]->getType() != 154
			&& tileMap[i]->getType() != 155
			&& tileMap[i]->getType() != 158
			&& tileMap[i]->getType() != 159
			&& tileMap[i]->getType() != 165
			&& tileMap[i]->getType() != 169
			&& tileMap[i]->getType() != 180
			&& tileMap[i]->getType() != 181
			&& tileMap[i]->getType() != 182
			&& tileMap[i]->getType() != 183
			&& tileMap[i]->getType() != 184
			&& tileMap[i]->getType() != 185
			&& tileMap[i]->getType() != 186
			&& tileMap[i]->getType() != 187
			&& tileMap[i]->getType() != 188
			&& tileMap[i]->getType() != 189
			&& tileMap[i]->getType() != 190
			&& tileMap[i]->getType() != 191
			//------------------------------------------------------------------------------------//
			//                                      MUNDO OSCURO								  //
			//------------------------------------------------------------------------------------//

			&& tileMap[i]->getType() != 195
			&& tileMap[i]->getType() != 196
			&& tileMap[i]->getType() != 197
			&& tileMap[i]->getType() != 199
			&& tileMap[i]->getType() != 200
			&& tileMap[i]->getType() != 201
			&& tileMap[i]->getType() != 202
			&& tileMap[i]->getType() != 211
			&& tileMap[i]->getType() != 212
			&& tileMap[i]->getType() != 213
			&& tileMap[i]->getType() != 214
			&& tileMap[i]->getType() != 215
			&& tileMap[i]->getType() != 216
			&& tileMap[i]->getType() != 225
			&& tileMap[i]->getType() != 226
			&& tileMap[i]->getType() != 227
			&& tileMap[i]->getType() != 228
			&& tileMap[i]->getType() != 309
			&& tileMap[i]->getType() != 334
			&& tileMap[i]->getType() != 335
			&& tileMap[i]->getType() != 345
			&& tileMap[i]->getType() != 346
			&& tileMap[i]->getType() != 347
			&& tileMap[i]->getType() != 348
			&& tileMap[i]->getType() != 349
			&& tileMap[i]->getType() != 350
			&& tileMap[i]->getType() != 353
			&& tileMap[i]->getType() != 354
			&& tileMap[i]->getType() != 360
			&& tileMap[i]->getType() != 364
			&& tileMap[i]->getType() != 375
			&& tileMap[i]->getType() != 376
			&& tileMap[i]->getType() != 377
			&& tileMap[i]->getType() != 378
			&& tileMap[i]->getType() != 379
			&& tileMap[i]->getType() != 380
			&& tileMap[i]->getType() != 382
			&& tileMap[i]->getType() != 384
			&& tileMap[i]->getType() != 383
			&& tileMap[i]->getType() != 385
			&& tileMap[i]->getType() != 386
			
			&& pMundo->checkCollision(box, tileMap[i]->getBox())))
		{
			aux = true;
		}
		i++;

	}
	return aux;
}

void Mapa::draw()const{
	for (int i = 0; i < TOTAL_TILES; ++i)
		tileMap[i]->render(pMundo->getCamera());
}
