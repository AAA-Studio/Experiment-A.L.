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

		//If the map was loaded fine
		return tilesLoaded;
	}
}

void  Mapa::buscaSpawn(){
	int i = 0;
	bool encontrado = false;
	int tipo = 0;

	if (pJuego->getNivel() == 0){
		x = 300;
		y = 300;
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
	
	while (!encontrado && i < TOTAL_TILES)
	{
		if (tileMap[i]->getType() == tipo){
			SDL_Rect rect = tileMap[i]->getBox();
			x = rect.x + rect.w/3;
			y = rect.y + rect.h/3;
			encontrado = true;
		}
		i++;
	}
}



bool Mapa::touchesWall(SDL_Rect box)
{
	//Go through the tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//If the tile is a wall type tile
		//-----------------------------------------------PUERTAS DE SUMAS----------------------------------
		//PUERTA ROJA
		if ((tileMap[i]->getType() == 150))
		{
			if (pMundo->checkCollision(box, tileMap[i]->getBox())){
				pJuego->borraEstado = true;
				pJuego->estadoEnum = MundoReal;
				pJuego->setNivel(-1);
				return true;
			}
		}
		//PUERTA GRIS
		if ((tileMap[i]->getType() == 155))
		{
			if (pMundo->checkCollision(box, tileMap[i]->getBox())){
				pJuego->borraEstado = true;
				pJuego->estadoEnum = MundoReal;
				pJuego->setNivel(1);
				return true;
			}

		}
		//PUERTA MORADA
		if ((tileMap[i]->getType() == 154))
		{
			if (pMundo->checkCollision(box, tileMap[i]->getBox())){
				pJuego->borraEstado = true;
				pJuego->estadoEnum = MundoReal;
				pJuego->setNivel(2);
				return true;
			}

		}
		//PUERTA ROSA
		if ((tileMap[i]->getType() == 140))
		{
			if (pMundo->checkCollision(box, tileMap[i]->getBox())){
				pJuego->borraEstado = true;
				pJuego->estadoEnum = MundoReal;
				pJuego->setNivel(-2);
				return true;
			}

		}
		//PUERTA PISTACHO
		if ((tileMap[i]->getType() == 158))
		{
			if (pMundo->checkCollision(box, tileMap[i]->getBox())){
				pJuego->borraEstado = true;
				pJuego->estadoEnum = MundoReal;
				pJuego->setNivel(3);
				return true;

			}

		}
		//PUERTA AZUL OSCURO
		if ((tileMap[i]->getType() == 165))
		{
			if (pMundo->checkCollision(box, tileMap[i]->getBox())){
				pJuego->borraEstado = true;
				pJuego->estadoEnum = MundoReal;
				pJuego->setNivel(-3);
				return true;

			}

		}
		//PUERTA BURDEOS
		if ((tileMap[i]->getType() == 159))
		{
			if (pMundo->checkCollision(box, tileMap[i]->getBox())){
				pJuego->borraEstado = true;
				pJuego->estadoEnum = MundoReal;
				pJuego->setNivel(4);
				return true;

			}

		}
		//PUERTA MARRÓN
		if ((tileMap[i]->getType() == 153))
		{

			if (pMundo->checkCollision(box, tileMap[i]->getBox())){
				pJuego->borraEstado = true;
				pJuego->estadoEnum = MundoReal;
				pJuego->setNivel(-4);
				return true;

			}

		}
		//PUERTA AZUL
		if ((tileMap[i]->getType() == 152))
		{

			if (pMundo->checkCollision(box, tileMap[i]->getBox())){
				pJuego->borraEstado = true;
				pJuego->estadoEnum = MundoReal;
				pJuego->setNivel(5);
				return true;

			}

		}
		// PUERTA VERDE
			if ((tileMap[i]->getType() == 151))
			{
				if (pMundo->checkCollision(box, tileMap[i]->getBox())){
					pJuego->borraEstado = true;
					pJuego->estadoEnum = MundoReal;
					pJuego->setNivel(-5);
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
				&& tileMap[i]->getType() != 191))

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
