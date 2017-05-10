#include "Mapa.h"
#include "Mundo.h"

Mapa::Mapa(MundoVirtual *pM, string mapa)
{
	camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	pMundo = pM;
	pJuego = pMundo->getPJ();
	nombreMapa = mapa;
	cargarMapa();
	buscaSpawn();
}


Mapa::~Mapa()
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
		y = 350;
		encontrado = true;
	}
	//sale en el spawn gris
	if (pJuego->getNivel() == -1)
		tipo = 185;
	//spawn rojo
	if (pJuego->getNivel() == 1)
		tipo = 180;

	//spawn rosa
	if (pJuego->getNivel() == 2)
		tipo = 191;

	//spawn morado
	if (pJuego->getNivel() == -2)
		tipo = 184;

	//spawn azul oscuro
	if (pJuego->getNivel() == 3)
		tipo = 190;

	//spawn pistacho
	if (pJuego->getNivel() == -3)
		tipo = 188;

	//spawn marrón
	if (pJuego->getNivel() == 4)
		tipo = 183;

	//spawn burdeos
	if (pJuego->getNivel() == -4)
		tipo = 189;

	//spawn verde
	if (pJuego->getNivel() == 5)
		tipo = 181;

	//spawn azul
	if (pJuego->getNivel() == -5)
		tipo = 182;
	//spawn en espejo
	if (pJuego->indiceMapas<6 && pJuego->getNivel() == -6)
		tipo = 169;
	//------------------------------------------------------------------------------------//
	//                                      MUNDO OSCURO								  //
	//------------------------------------------------------------------------------------//
	//spawn espejo en oscuro
	if (pJuego->indiceMapas>5 && pJuego->getNivel() == 6)
		tipo = 364;
	//spawn azul en oscuro
	if (pJuego->indiceMapas>5 && pJuego->getNivel() == -5)
		tipo = 377;
	//spawn verde en oscuro
	if (pJuego->indiceMapas>5 && pJuego->getNivel() == 5)
		tipo = 376;
	//spawn rojo en oscuro
	if (pJuego->indiceMapas>5 && pJuego->getNivel() == 1)
		tipo = 375;
	//spawn gris en oscuro
	if (pJuego->indiceMapas>5 && pJuego->getNivel() == -1)
		tipo = 380;
	//spawn morado en oscuro
	if (pJuego->indiceMapas>5 && pJuego->getNivel() == -2)
		tipo = 379;
	//spawn rosa en oscuro
	if (pJuego->indiceMapas>5 && pJuego->getNivel() == 2)
		tipo = 386;
	//spawn burdeos en oscuro
	if (pJuego->indiceMapas>5 && pJuego->getNivel() == -4)
		tipo = 384;
	//spawn pistacho en oscuro
	if (pJuego->indiceMapas>5 && pJuego->getNivel() == -3)
		tipo = 383;
	//spawn azul oscuro en oscuro
	if (pJuego->indiceMapas>5 && pJuego->getNivel() == 3)
		tipo = 385;
	//spawn pistacho en oscuro
	if (pJuego->indiceMapas>5 && pJuego->getNivel() == 4)
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
}



bool Mapa::touchesWall(SDL_Rect box)
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
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(-1);
						return true;
					}
				}
					//PUERTA GRIS
					if ((tileMap[i]->getType() == 155))
					{
						felpudo = tileMap[i]->getBox();
						felpudo.x = felpudo.x + 10;
						felpudo.y = felpudo.y + 25;
						felpudo.h = felpudo.h - 20;
						felpudo.w = felpudo.w - 20;

						if (pMundo->checkCollision(box, felpudo)){
							pJuego->borraEstado = true;
							pJuego->estadoEnum = MundoReal;
							pJuego->setNivel(1);
							return true;
						}

					}
				//PUERTA MORADA
				if ((tileMap[i]->getType() == 154))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 20;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(2);
						return true;
					}

				}
				//PUERTA ROSA
				if ((tileMap[i]->getType() == 140))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(-2);
						return true;
					}

				}
				//PUERTA PISTACHO
				if (pJuego->getPuerta(0) && (tileMap[i]->getType() == 158))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(3);
						return true;

					}

				}
				//PUERTA AZUL OSCURO
				if ((tileMap[i]->getType() == 165))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(-3);
						return true;

					}

				}
				//PUERTA BURDEOS
				if ( false && (tileMap[i]->getType() == 159))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(4);
						return true;

					}

				}
				//PUERTA MARRÓN
				if ((tileMap[i]->getType() == 153))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(-4);
						return true;

					}

				}
				//PUERTA AZUL
				if ((pJuego->getLLavesCogidas(0) )&&(tileMap[i]->getType() == 152))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 25;
					
					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(5);
						return true;

					}

				}
				// PUERTA VERDE
				if ((tileMap[i]->getType() == 151))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(-5);
						return true;

					}

				}

				// ESPEJO
				if ((tileMap[i]->getType() == 114))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(6);
						return true;

					}

				}

				//------------------------------------------------------------------------------------//
				//                                      MUNDO OSCURO								  //
				//------------------------------------------------------------------------------------//

				//If the tile is a wall type tile
				//-----------------------------------------------PUERTAS DE SUMAS----------------------------------
				//PUERTA ROJA (OSCURO)
				if ((tileMap[i]->getType() == 345))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(-1);
						return true;
					}
				}
				//PUERTA GRIS (OSCURO)
				if ((tileMap[i]->getType() == 350))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 20;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(1);
						return true;
					}

				}
				//PUERTA MORADA (OSCURO)
				if ((tileMap[i]->getType() == 349))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 20;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(2);
						return true;
					}

				}
				//PUERTA ROSA (OSCURO)
				if ((tileMap[i]->getType() == 335))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(-2);
						return true;
					}

				}
				//PUERTA PISTACHO (OSCURO)
				if ((tileMap[i]->getType() == 353))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(3);
						return true;

					}

				}
				//PUERTA AZUL OSCURO (OSCURO)
				if ((tileMap[i]->getType() == 360))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(-3);
						return true;

					}

				}
				//PUERTA BURDEOS (OSCURO)
				if ((tileMap[i]->getType() == 354))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(4);
						return true;

					}

				}
				//PUERTA MARRÓN
				if ((tileMap[i]->getType() == 348))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(-4);
						return true;

					}

				}
				//PUERTA AZUL (OSCURO)
				if ((tileMap[i]->getType() == 347))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 25;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(5);
						return true;

					}

				}
				// PUERTA VERDE (OSCURO)
				if ((tileMap[i]->getType() == 346))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(-5);
						return true;

					}

				}

				// ESPEJO (OSCURO)
				if ((tileMap[i]->getType() == 309))
				{
					felpudo = tileMap[i]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;
					
					if (pMundo->checkCollision(box, felpudo)){
						pJuego->borraEstado = true;
						pJuego->estadoEnum = MundoReal;
						pJuego->setNivel(-6);
						return true;

					}

				}

				//No colisionar con suelo y alfombras
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
					))

				{
					//Si se choca con la pared
					if (pMundo->checkCollision(box, tileMap[i]->getBox()))
						return true;
				}
	}

	//If no wall tiles were touched
	return false;

}

void Mapa::draw()const{
	for (int i = 0; i < TOTAL_TILES; ++i)
		tileMap[i]->render(camera);

}
