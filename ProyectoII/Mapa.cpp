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
	//------------------------------------------------------ PLANTA 5 ------------------------------------------------------------//

	//sale en el spawn gris
	else if (pJuego->indiceMapas<24 && pJuego->getNivel() == -1)
		tipo = 185;
	//spawn rojo
	else if (pJuego->indiceMapas<24 && pJuego->getNivel() == 1)
		tipo = 180;

	//spawn rosa
	else if (pJuego->indiceMapas<24 && pJuego->getNivel() == 2)
		tipo = 191;

	//spawn morado
	else if (pJuego->indiceMapas<24 && pJuego->getNivel() == -2)
		tipo = 184;
	
	//spawn azul oscuro
	else if (pJuego->indiceMapas<24 && pJuego->getNivel() == 3)
		tipo = 183;

	//spawn pistacho
	else if (pJuego->indiceMapas<24 && pJuego->getNivel() == -3)
		tipo = 188;

	//spawn marrón
	else if (pJuego->indiceMapas<24 && pJuego->getNivel() == 4)
		tipo = 190;

	//spawn burdeos
	else if (pJuego->indiceMapas<24 && pJuego->getNivel() == -4)
		tipo = 189;

	//spawn verde
	else if (pJuego->indiceMapas<24 && pJuego->getNivel() == 5)
		tipo = 181;

	//spawn azul
	else if (pJuego->indiceMapas<24 && pJuego->getNivel() == -5)
		tipo = 182;

	//spawn en espejo
	else if (pJuego->indiceMapas<24 && pJuego->getNivel() == -24)
		tipo = 169;
	//spawn amarillo
	else if (pJuego->indiceMapas<24 && pJuego->getNivel() == 6)
		tipo = 186;
	//spawn naranja
	else if (pJuego->indiceMapas<24 && pJuego->getNivel() == -6)
		tipo = 187;
	//------------------------------------------------------------------------------------//
	//                                      MUNDO OSCURO								  //
	//------------------------------------------------------------------------------------//
	//spawn espejo en oscuro
	else if (pJuego->indiceMapas>23 && pJuego->getNivel() == 24)
		tipo = 514;
	//spawn azul en oscuro
	else if (pJuego->indiceMapas>23 && pJuego->getNivel() == -5)
		tipo = 527;
	//spawn verde en oscuro
	else if (pJuego->indiceMapas>23 && pJuego->getNivel() == 5)
		tipo = 526;
	//spawn rojo en oscuro
	else if (pJuego->indiceMapas>23 && pJuego->getNivel() == 1)
		tipo = 525;
	//spawn gris en oscuro
	else if (pJuego->indiceMapas>23 && pJuego->getNivel() == -1)
		tipo = 530;
	//spawn morado en oscuro
	else if (pJuego->indiceMapas>23 && pJuego->getNivel() == -2)
		tipo = 529;
	//spawn rosa en oscuro
	else if (pJuego->indiceMapas>23 && pJuego->getNivel() == 2)
		tipo = 536;
	//spawn burdeos en oscuro
	else if (pJuego->indiceMapas>23 && pJuego->getNivel() == -4)
		tipo = 534;
	//spawn pistacho en oscuro
	else if (pJuego->indiceMapas>23 && pJuego->getNivel() == -3)
		tipo = 533;
	//spawn caca en oscuro
	else if (pJuego->indiceMapas>23 && pJuego->getNivel() == 3)
		tipo = 528;
	//spawn azul oscuro en oscuro
	else if (pJuego->indiceMapas>23 && pJuego->getNivel() == 4)
		tipo = 535;
	//spawn amarillo oscuro
	else if (pJuego->indiceMapas>23 && pJuego->getNivel() == 6)
		tipo = 531;
	//spawn naranja oscuro
	else if (pJuego->indiceMapas>23 && pJuego->getNivel() == -6)
		tipo = 532;
	int x, y, h, w;
	if (pJuego->indiceMapas < 24){
		x = 0;
		w = 800;
		if (pJuego->indiceMapas >= 0 && pJuego->indiceMapas < 6)
		{
			// planta de 6
			y = 0;
			h = 3840;

		}
		else if (pJuego->indiceMapas >= 6 && pJuego->indiceMapas < 12)
		{
			// 2 plantas de 6
			y = 3840;
			h = 3840*2;

		}
		else if (pJuego->indiceMapas >= 12 && pJuego->indiceMapas < 17)
		{	// 2 plantas de 6 y 1 planta de 5
			y = 3840*2;
			h = 3840*2 + 3200;

		}
		else if(pJuego->indiceMapas >= 17 && pJuego->indiceMapas < 22)
		{
			// 2 plantas de 6 y 2 plantas de 5
			y = 3840*2 + 3200;
			h = 3840*2 + 3200*2;

		}
		else if(pJuego->indiceMapas >= 22 && pJuego->indiceMapas < 24)
		{
			// 2 plantas de 6 y 2 plantas de 5 y 1 planta de 2
			y = 3840 * 2 + 3200 * 2;
			h = 3840 * 2 + 3200 * 2 + 640*2;

		}
	}
	else {
		x = 800;
		w = 1600;
		if (pJuego->indiceMapas >= 24 && pJuego->indiceMapas < 30)
		{
			// planta de 6
			y = 0;
			h = 3840;

		}
		else if (pJuego->indiceMapas >= 30 && pJuego->indiceMapas < 36)
		{
			// 2 plantas de 6
			y = 3840;
			h = 3840 * 2;

		}
		else if (pJuego->indiceMapas >= 36 && pJuego->indiceMapas < 41)
		{	// 2 plantas de 6 y 1 planta de 5
			y = 3840 * 2;
			h = 3840 * 2 + 3200;

		}
		else if (pJuego->indiceMapas >= 41 && pJuego->indiceMapas < 46)
		{
			// 2 plantas de 6 y 2 plantas de 5
			y = 3840 * 2 + 3200;
			h = 3840 * 2 + 3200 * 2;

		}
		else if (pJuego->indiceMapas >= 46 && pJuego->indiceMapas < 48)
		{
			// 2 plantas de 6 y 2 plantas de 5 y 1 planta de 2
			y = 3840 * 2 + 3200 * 2;
			h = 3840 * 2 + 3200 * 2 + 640 * 2;

		}
	}
	while (!encontrado && i < TOTAL_TILES)
	{
		if (tileMap[i]->getType() == tipo && tileMap[i]->getBox().x >= x && tileMap[i]->getBox().x + tileMap[i]->getBox().w <= w
			&& tileMap[i]->getBox().y >= y && tileMap[i]->getBox().y + tileMap[i]->getBox().h <= h){
			SDL_Rect rect = tileMap[i]->getBox();
			this->x = rect.x;
			this->y = rect.y;
			encontrado = true;
		}
		i++;
	}

	pMundo->cambiaPosPSJ(this->x, this->y);
	setCamera();
}

//Pone la cámara en el centro de cada nivel cuando se pasa de una sala a otra
void Mapa::setCamera()
{
	int ancho;
	if (pJuego->indiceMapas < 24)
		ancho = 0;
	else 
		ancho = 1;
	pMundo->setCamera(800 * ancho, pJuego->indiceMapas % 24 * 640);
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
			if ((tileMap[indice]->getType() == 150))
			{
				felpudo = tileMap[indice]->getBox();
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
			else if ((tileMap[indice]->getType() == 155))
			{
				felpudo = tileMap[indice]->getBox();
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
			else if ((tileMap[indice]->getType() == 154))
			{
				felpudo = tileMap[indice]->getBox();
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
			else if ((tileMap[indice]->getType() == 140))
			{
				felpudo = tileMap[indice]->getBox();
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
			else if (tileMap[indice]->getType() == 158)
			{
				if (pJuego->getPuerta(0) && pJuego->indiceMapas == 0){
					felpudo = tileMap[indice]->getBox();
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
				else if (pJuego->indiceMapas != 0){
					felpudo = tileMap[indice]->getBox();
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
					pJuego->setNivel(-4);
					tipo = 165;
					buscaSpawn();
					return true;

				}

			}
			//PUERTA BURDEOS
			else if (tileMap[indice]->getType() == 159)
			{
				if (pJuego->indiceMapas == 0 && false){
					felpudo = tileMap[indice]->getBox();
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
				else if(pJuego->indiceMapas!=0) {
					felpudo = tileMap[indice]->getBox();
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
					pJuego->setNivel(-3);
					tipo = 153;
					buscaSpawn();
					return true;

				}

			}
			//PUERTA AZUL
			else if (tileMap[indice]->getType() == 152)
			{
				if ((pJuego->getLLavesCogidas(0) || Puerta1Abierta) && pJuego->indiceMapas == 0){
					felpudo = tileMap[indice]->getBox();
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
				else if (pJuego->indiceMapas != 0){
					felpudo = tileMap[indice]->getBox();
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

			}
			// PUERTA VERDE
			else if ((tileMap[indice]->getType() == 151))
			{
				felpudo = tileMap[indice]->getBox();
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
			// PUERTA NARANJA
			else if ((tileMap[indice]->getType() == 157))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(6);
					tipo = 157;
					buscaSpawn();
					return true;

				}

			}
			// PUERTA GRIS OSCURA
			else if ((tileMap[indice]->getType() == 174))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(-6);
					tipo = 174;
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
					pJuego->setNivel(24);
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
			else if ((tileMap[indice]->getType() == 495))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(-1);
					tipo = 495;
					buscaSpawn();
					return true;
				}
			}
			//PUERTA GRIS (OSCURO)
			else if ((tileMap[indice]->getType() == 500))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 20;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(1);
					tipo = 500;
					buscaSpawn();
					return true;
				}

			}
			//PUERTA MORADA (OSCURO)
			else if ((tileMap[indice]->getType() == 499))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 20;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(2);
					tipo = 499;
					buscaSpawn();
					return true;
				}

			}
			//PUERTA ROSA (OSCURO)
			else if ((tileMap[indice]->getType() == 485))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(-2);
					tipo = 485;
					buscaSpawn();
					return true;
				}

			}
			//PUERTA PISTACHO (OSCURO)
			else if ((tileMap[indice]->getType() == 503))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(3);
					tipo = 503;
					buscaSpawn();
					return true;

				}

			}
			//PUERTA AZUL OSCURO (OSCURO)
			else if ((tileMap[indice]->getType() == 510))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(-4);
					tipo = 510;
					buscaSpawn();
					return true;

				}

			}
			//PUERTA BURDEOS (OSCURO)
			else if ((tileMap[indice]->getType() == 504))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(4);
					tipo = 504;
					buscaSpawn();
					return true;

				}

			}
			//PUERTA MARRÓN
			else if ((tileMap[indice]->getType() == 498))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(-3);
					tipo = 498;
					buscaSpawn();
					return true;

				}

			}
			//PUERTA AZUL (OSCURO)
			else if ((tileMap[indice]->getType() == 497))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 25;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(5);
					tipo = 497;
					buscaSpawn();
					return true;

				}

			}
			// PUERTA VERDE (OSCURO)
			else if ((tileMap[indice]->getType() == 496))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(-5);
					tipo = 496;
					buscaSpawn();
					return true;

				}

			}
			// PUERTA NARANJA (OSCURO)
			else if ((tileMap[indice]->getType() == 502))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(6);
					tipo = 502;
					buscaSpawn();
					return true;

				}

			}
			// PUERTA GRIS OSCURP (OSCURO)
			else if ((tileMap[indice]->getType() == 519))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(-6);
					tipo = 519;
					buscaSpawn();
					return true;

				}

			}

			// ESPEJO (OSCURO)
			else if ((tileMap[indice]->getType() == 459))
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pJuego->setNivel(-24);
					tipo = 459;
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
				&& tileMap[indice]->getType() != 4
				&& tileMap[indice]->getType() != 5
				&& tileMap[indice]->getType() != 6
				&& tileMap[indice]->getType() != 7
				&& tileMap[indice]->getType() != 16
				&& tileMap[indice]->getType() != 17
				&& tileMap[indice]->getType() != 18
				&& tileMap[indice]->getType() != 19
				&& tileMap[indice]->getType() != 20
				&& tileMap[indice]->getType() != 21
				&& tileMap[indice]->getType() != 22
				&& tileMap[indice]->getType() != 23
				&& tileMap[indice]->getType() != 27
				&& tileMap[indice]->getType() != 28
				&& tileMap[indice]->getType() != 29
				&& tileMap[indice]->getType() != 30
				&& tileMap[indice]->getType() != 31
				&& tileMap[indice]->getType() != 32
				&& tileMap[indice]->getType() != 33
				&& tileMap[indice]->getType() != 42
				&& tileMap[indice]->getType() != 43
				&& tileMap[indice]->getType() != 44
				&& tileMap[indice]->getType() != 54
				&& tileMap[indice]->getType() != 55
				&& tileMap[indice]->getType() != 56
				&& tileMap[indice]->getType() != 57
				&& tileMap[indice]->getType() != 58
				&& tileMap[indice]->getType() != 59
				&& tileMap[indice]->getType() != 64
				&& tileMap[indice]->getType() != 114
				&& tileMap[indice]->getType() != 140
				&& tileMap[indice]->getType() != 150
				&& tileMap[indice]->getType() != 151
				&& tileMap[indice]->getType() != 152
				&& tileMap[indice]->getType() != 153
				&& tileMap[indice]->getType() != 154
				&& tileMap[indice]->getType() != 155
				&& tileMap[indice]->getType() != 156
				&& tileMap[indice]->getType() != 157
				&& tileMap[indice]->getType() != 158
				&& tileMap[indice]->getType() != 159
				&& tileMap[indice]->getType() != 165
				&& tileMap[indice]->getType() != 169
				&& tileMap[indice]->getType() != 174
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
				&& tileMap[indice]->getType() != 338
				&& tileMap[indice]->getType() != 339
				&& tileMap[indice]->getType() != 340
				//------------------------------------------------------------------------------------//
				//                                      MUNDO OSCURO								  //
				//------------------------------------------------------------------------------------//

				&& tileMap[indice]->getType() != 345
				&& tileMap[indice]->getType() != 346
				&& tileMap[indice]->getType() != 347
				&& tileMap[indice]->getType() != 348
				&& tileMap[indice]->getType() != 349
				&& tileMap[indice]->getType() != 350
				&& tileMap[indice]->getType() != 351
				&& tileMap[indice]->getType() != 352
				&& tileMap[indice]->getType() != 361
				&& tileMap[indice]->getType() != 362
				&& tileMap[indice]->getType() != 363
				&& tileMap[indice]->getType() != 364
				&& tileMap[indice]->getType() != 365
				&& tileMap[indice]->getType() != 366
				&& tileMap[indice]->getType() != 367
				&& tileMap[indice]->getType() != 368
				&& tileMap[indice]->getType() != 372
				&& tileMap[indice]->getType() != 373
				&& tileMap[indice]->getType() != 374
				&& tileMap[indice]->getType() != 375
				&& tileMap[indice]->getType() != 376
				&& tileMap[indice]->getType() != 377
				&& tileMap[indice]->getType() != 378
				&& tileMap[indice]->getType() != 387
				&& tileMap[indice]->getType() != 388
				&& tileMap[indice]->getType() != 389
				&& tileMap[indice]->getType() != 399
				&& tileMap[indice]->getType() != 400
				&& tileMap[indice]->getType() != 401
				&& tileMap[indice]->getType() != 402
				&& tileMap[indice]->getType() != 403
				&& tileMap[indice]->getType() != 404
				&& tileMap[indice]->getType() != 409
				&& tileMap[indice]->getType() != 459
				&& tileMap[indice]->getType() != 485
				&& tileMap[indice]->getType() != 495
				&& tileMap[indice]->getType() != 496
				&& tileMap[indice]->getType() != 497
				&& tileMap[indice]->getType() != 498
				&& tileMap[indice]->getType() != 499
				&& tileMap[indice]->getType() != 500
				&& tileMap[indice]->getType() != 501
				&& tileMap[indice]->getType() != 502
				&& tileMap[indice]->getType() != 503
				&& tileMap[indice]->getType() != 504
				&& tileMap[indice]->getType() != 510
				&& tileMap[indice]->getType() != 514
				&& tileMap[indice]->getType() != 519
				&& tileMap[indice]->getType() != 525
				&& tileMap[indice]->getType() != 526
				&& tileMap[indice]->getType() != 527
				&& tileMap[indice]->getType() != 528
				&& tileMap[indice]->getType() != 529
				&& tileMap[indice]->getType() != 530
				&& tileMap[indice]->getType() != 531
				&& tileMap[indice]->getType() != 532
				&& tileMap[indice]->getType() != 533
				&& tileMap[indice]->getType() != 534
				&& tileMap[indice]->getType() != 535
				&& tileMap[indice]->getType() != 536
				&& tileMap[indice]->getType() != 683
				&& tileMap[indice]->getType() != 684
				&& tileMap[indice]->getType() != 685

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
