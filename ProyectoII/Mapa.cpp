#include "Mapa.h"
#include "Mundo.h"

Mapa::Mapa(Juego*pJ, MundoVirtual *pM, string mapa)
{
	camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	pJuego = pJ;
	pMundo = pM;
	nombreMapa = mapa;
	cargarMapa();
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
				tileMap[i] = new Tile(x, y, tileType, pJuego);
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
void  Mapa::buscaSpawn(int tipo, int& x, int& y){
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		if (tileMap[i]->getType() == tipo){
			SDL_Rect rect = tileMap[i]->getBox();
			x = rect.x + rect.w/2;
			y = rect.y + rect.h/2;
		}
	}
}



bool Mapa::touchesWall(SDL_Rect box)
{
	//Go through the tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//If the tile is a wall type tile
		//-----------------------------------------------PUERTAS DE SUMAS----------------------------------
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

		//-----------------------------------------------PUERTAS DE RESTAS----------------------------------
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
		
		if ((tileMap[i]->getType() >1000)) //&& (tiles[i]->getType() <= TILE_3))

		{
			//Si se choca con la pared
			if (pMundo->checkCollision(box, tileMap[i]->getBox())){

				return true;

			}

		}
	}

	//If no wall tiles were touched
	return false;

}

void Mapa::draw()const{
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		tileMap[i]->render(camera);
	}

}
