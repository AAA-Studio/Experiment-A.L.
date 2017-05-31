#include "Mapa.h"
#include "Mundo.h"
#include <fstream>

Mapa::Mapa(MundoVirtual *pM, string mapa) : pMundo(pM), nombreMapa(mapa)
{
	pJuego = pM->getPJ();
	cargarMapa();
	buscaSpawn();
	setCamera();
	azulCP4O = naranajaP5R = naranjaP4R = pistachoP3O = azulCP2R = azulCP5R = false;
	encendido = encendido2 = false;

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
bool Mapa::pulsados()
{
	if (encendido && encendido2)
		return true;
	else
		return false;
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

	//VEMOS QUE TIPO DE SPAWN DEBE BUSCAR

	//------------------------------------------------------------------------------------//
	//                                      MUNDO REAL								      //
	//------------------------------------------------------------------------------------//


	if (pMundo->getIndiceMapa() < 24){
		//sale en el spawn gris
		if (pMundo->getNivel() == -1)
			tipo = 185;
		//spawn rojo
		else if (pMundo->getNivel() == 1)
			tipo = 180;

		//spawn rosa
		else if (pMundo->getNivel() == 2)
			tipo = 191;

		//spawn morado
		else if (pMundo->getNivel() == -2)
			tipo = 184;

		//spawn azul oscuro
		else if (pMundo->getNivel() == 3)
			tipo = 183;

		//spawn pistacho
		else if (pMundo->getNivel() == -3)
			tipo = 188;

		//spawn marrón
		else if (pMundo->getNivel() == 4)
			tipo = 190;

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
		else if (pMundo->getNivel() == -24)
		{

			tipo = 169;
			pMundo->getPJ()->getResources()->getMusica(JuegoSDL::Musica_t::MOscuro)->closeAndLoad();
			pMundo->getPJ()->getResources()->getMusica(JuegoSDL::Musica_t::MReal)->play();
		}
		//spawn amarillo
		else if (pMundo->getNivel() == 6)
			tipo = 186;
		//spawn naranja
		else if (pMundo->getNivel() == -6)
			tipo = 187;
	}
	//------------------------------------------------------------------------------------//
	//                                      MUNDO OSCURO								  //
	//------------------------------------------------------------------------------------//
	else{
		//spawn espejo en oscuro
		if (pMundo->getNivel() == 24)
		{

			tipo = 514;
			pMundo->getPJ()->getResources()->getMusica(JuegoSDL::Musica_t::MReal)->closeAndLoad();
			pMundo->getPJ()->getResources()->getMusica(JuegoSDL::Musica_t::MOscuro)->play();
		}
		//spawn azul en oscuro
		else if (pMundo->getNivel() == -5){
			tipo = 527;
		}
		//spawn verde en oscuro
		else if (pMundo->getNivel() == 5)
			tipo = 526;
		//spawn rojo en oscuro
		else if (pMundo->getNivel() == 1)
			tipo = 525;
		//spawn gris en oscuro
		else if (pMundo->getNivel() == -1)
			tipo = 530;
		//spawn morado en oscuro
		else if (pMundo->getNivel() == -2)
			tipo = 529;
		//spawn rosa en oscuro
		else if (pMundo->getNivel() == 2)
			tipo = 536;
		//spawn burdeos en oscuro
		else if (pMundo->getNivel() == -4)
			tipo = 534;
		//spawn pistacho en oscuro
		else if (pMundo->getNivel() == -3)
			tipo = 533;
		//spawn caca en oscuro
		else if (pMundo->getNivel() == 3)
			tipo = 528;
		//spawn azul oscuro en oscuro
		else if (pMundo->getNivel() == 4)
			tipo = 535;
		//spawn amarillo oscuro
		else if (pMundo->getNivel() == 6)
			tipo = 531;
		//spawn naranja oscuro
		else if (pMundo->getNivel() == -6)
			tipo = 532;
	}

	//////////////////////////////RESTRICCIONES PARA BUSCAR EL SPAWN EN DONDE SE DEBE ////////////////////////////////////////
	int x, y, h, w;
	if (pMundo->getIndiceMapa() < 24){
		x = 0;
		w = 800;
		//Planta 5
		if (pMundo->getIndiceMapa() >= 0 && pMundo->getIndiceMapa() < 6)
		{
			// planta de 6
			y = 0;
			h = 3840;

		}
		//Planta 4
		else if (pMundo->getIndiceMapa() >= 6 && pMundo->getIndiceMapa() < 12)
		{
			// 2 plantas de 6
			y = 3840;
			h = 3840 * 2;

		}
		//Planta 3
		else if (pMundo->getIndiceMapa() >= 12 && pMundo->getIndiceMapa() < 17)
		{	// 2 plantas de 6 y 1 planta de 5
			y = 3840 * 2;
			h = 3840 * 2 + 3200;

		}
		//Planta 2
		else if (pMundo->getIndiceMapa() >= 17 && pMundo->getIndiceMapa() < 22)
		{
			// 2 plantas de 6 y 2 plantas de 5
			y = 3840 * 2 + 3200;
			h = 3840 * 2 + 3200 * 2;

		}
		//Planta 1
		else if (pMundo->getIndiceMapa() >= 22 && pMundo->getIndiceMapa() < 24)
		{
			// 2 plantas de 6 y 2 plantas de 5 y 1 planta de 2
			y = 3840 * 2 + 3200 * 2;
			h = 3840 * 2 + 3200 * 2 + 640 * 2;

		}
	}
	else {
		x = 800;
		w = 1600;
		if (pMundo->getIndiceMapa() >= 24 && pMundo->getIndiceMapa() < 30)
		{
			// planta de 6
			y = 0;
			h = 3840;

		}
		else if (pMundo->getIndiceMapa() >= 30 && pMundo->getIndiceMapa()< 36)
		{
			// 2 plantas de 6
			y = 3840;
			h = 3840 * 2;

		}
		else if (pMundo->getIndiceMapa() >= 36 && pMundo->getIndiceMapa()< 41)
		{	// 2 plantas de 6 y 1 planta de 5
			y = 3840 * 2;
			h = 3840 * 2 + 3200;

		}
		else if (pMundo->getIndiceMapa() >= 41 && pMundo->getIndiceMapa() < 46)
		{
			// 2 plantas de 6 y 2 plantas de 5
			y = 3840 * 2 + 3200;
			h = 3840 * 2 + 3200 * 2;

		}
		else if (pMundo->getIndiceMapa() >= 46 && pMundo->getIndiceMapa() < 48)
		{
			// 2 plantas de 6 y 2 plantas de 5 y 1 planta de 2
			y = 3840 * 2 + 3200 * 2;
			h = 3840 * 2 + 3200 * 2 + 640 * 2;

		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// se busca el spawn donde se debe
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

	if (pMundo->getPersonaje() != nullptr)
	{
		SDL_Rect rectPj = pMundo->getPersonaje()->getRect();
		pMundo->getPersonaje()->setRect({ this->x, this->y, rectPj.w, rectPj.h });
	}
	setCamera();
}

//Pone la cámara en el centro de cada nivel cuando se pasa de una sala a otra
void Mapa::setCamera()
{
	int ancho;
	if (pMundo->getIndiceMapa() < 24)
		ancho = 0;
	else
		ancho = 1;
	pMundo->setCamera(800 * ancho, pMundo->getIndiceMapa() % 24 * 640);
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
			if (tileMap[indice]->getType() == 150)
			{
					felpudo = tileMap[indice]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						
						pMundo->setNivel(-1);
						tipo = 150;
						
						pMundo->setPasoNivel(true);
						pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
						return true;
					}
			}
			//PUERTA GRIS
			else if (tileMap[indice]->getType() == 155)
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 20;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(1);
					tipo = 155;
			
					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
					return true;
				}

			}
			//PUERTA MORADA
			else if (tileMap[indice]->getType() == 154)
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 20;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(2);
					tipo = 154;
					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
					return true;
				}

			}
			//PUERTA ROSA
			else if (tileMap[indice]->getType() == 140)
			{
					felpudo = tileMap[indice]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pMundo->setNivel(-2);
						tipo = 140;
						pMundo->setPasoNivel(true);
						pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
						return true;
					}
			}
			//PUERTA PISTACHO
			else if (tileMap[indice]->getType() == 158)
			{
				//Planta 5 necesitas el codigo
				//Caso en el que aun no he metido la combinacion
				if (pMundo->getIndiceMapa() == 0 && !pJuego->getPuerta(0)){
					felpudo = tileMap[indice]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;
					if (pMundo->checkCollision(box, felpudo)){
						tipo = 158;
						pMundo->setPuertaCerrada(true);
						pMundo->getTexturaPCerrada()->loadFromText(pJuego->getRender(), "Cerrada.", { 255, 255, 255, 1 }, *pMundo->getFuente());
						return true;

					}
					//Caso en el que no colisiono con la puerta
					else
						pMundo->setPuertaCerrada(false);
				}
				//Caso en el que ya puedo abrir la puerta porque he metido la combinacion
				if (pJuego->getPuerta(0) && pMundo->getIndiceMapa() == 0){
					pMundo->setPuertaCerrada(false);//La puerta ya no esta cerrada en este caso
					felpudo = tileMap[indice]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;
					if (pMundo->checkCollision(box, felpudo)){
						pMundo->setNivel(3);
						tipo = 158;

						pMundo->setPasoNivel(true);
						pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
						return true;
					}					
				
				}
				//En las demas no
				else if (pMundo->getIndiceMapa() != 0){
				//	pMundo->setPuertaCerrada(false);//La puerta ya no esta cerrada en este caso

					felpudo = tileMap[indice]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pMundo->setNivel(3);
						tipo = 158;
						pMundo->setPasoNivel(true);
						pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
						return true;

					}
				}
			}
			//PUERTA AZUL OSCURO
			else if (tileMap[indice]->getType() == 165)
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.y = felpudo.y + 25;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(-4);
					tipo = 165;
					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
					return true;

				}

			}
			//PUERTA BURDEOS
			else if (tileMap[indice]->getType() == 159)
			{
				//Como en la planta 5 esta bloqueada miro las demas
				if (pMundo->getIndiceMapa() != 0) {
					felpudo = tileMap[indice]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pMundo->setNivel(4);
						tipo = 159;
						
						pMundo->setPasoNivel(true);
						pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
						return true;
					}
				}
				else {
					felpudo = tileMap[indice]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;
					if (pMundo->checkCollision(box, felpudo)){
						tipo = 159;
						//Escribo el texto de que la puerta esta cerrada
						pMundo->setPuertaCerrada(true);
						pMundo->getTexturaPCerrada()->loadFromText(pJuego->getRender(), "Cerrada.", { 255, 255, 255, 1 }, *pMundo->getFuente());
						if (contadorParaSonido1 > 100){//NICE
							contadorParaSonido1 = 0;
							pMundo->getPJ()->getResources()->getEfecto(3)->play(0);
						}
						else
							contadorParaSonido1++;
						return true;
					}
					else
						pMundo->setPuertaCerrada(false);
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
					pMundo->setNivel(-3);
					tipo = 153;
					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
					return true;

				}

			}
			//PUERTA AZUL CLARO
			else if (tileMap[indice]->getType() == 152)
			{
				//Caso en el que estoy en la planta 5 no he cogido la llave
				if (pMundo->getIndiceMapa() == 0 && !pMundo->getLLavesCogidas(0) && !azulCP5R){
					felpudo = tileMap[indice]->getBox();
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 25;
					if (pMundo->checkCollision(box, felpudo)){
						pMundo->setPuertaCerrada(true);
						pMundo->getTexturaPCerrada()->loadFromText(pJuego->getRender(), "Cerrada.", { 255, 255, 255, 1 }, *pMundo->getFuente());
						if (contadorParaSonido2 > 100){//NICE LVL 2
							contadorParaSonido2 = 0;
							pMundo->getPJ()->getResources()->getEfecto(3)->play(0);
						}
						else
							contadorParaSonido2++;
						return true;

					}
					//Caso en el que no colisiono con la puerta
					else
						pMundo->setPuertaCerrada(false);
				}
				//necesitas llave en el nivel 1, ya se ha cogido
				if ((pMundo->getLLavesCogidas(0) || azulCP5R) && pMundo->getIndiceMapa() == 0){
					felpudo = tileMap[indice]->getBox();
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 25;

					if (pMundo->checkCollision(box, felpudo)){
						//Por si tienes dos
						if (!azulCP5R && pMundo->getLLavesCogidas(1)){
							azulCP5R = true;
							pMundo->setLlaveCogida(0);
						}
						else if (!azulCP5R && pMundo->getLLavesCogidas(0)){
							azulCP5R = true;
							pMundo->setLlaveCogida(0);
						}
						pMundo->setNivel(5);
						tipo = 152;
						pMundo->setPasoNivel(true);
						pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
						return true;
					}
				}
				//necesitas ambos pulsadores en la planta 3 (Paso de la planta 3 a la 2)
				else if (pulsados() && pMundo->getIndiceMapa() == 12){
					//Si es horizontal ponemos el collider bien
					felpudo = tileMap[indice]->getBox();
					felpudo.y = felpudo.y - 5;
					felpudo.x = felpudo.x + 7;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 25;

					if (pMundo->checkCollision(box, felpudo)){
						pMundo->setNivel(5);
						tipo = 152;
						pMundo->setPasoNivel(true); 
						pMundo->setTextoArriba(true);
						if (pMundo->getIndiceMapa() == 17) {//ENTIENDO QUE ESTOY EN LA PLANTA 3
							pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 2", { 255, 255, 255, 1 }, *pMundo->getFuente());
						}
						pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
						return true;
					}
				}
				else if ((pMundo->getLLavesCogidas(0) || azulCP2R) && pMundo->getIndiceMapa() == 17){
					//Si es horizontal ponemos el collider bien
					felpudo = tileMap[indice]->getBox();
					felpudo.y = felpudo.y - 5;
					felpudo.x = felpudo.x + 7;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 25;

					if (pMundo->checkCollision(box, felpudo)){
						//Por si tienes dos
						if (!azulCP2R && pMundo->getLLavesCogidas(1)){
							azulCP2R = true;
							pMundo->setLlaveCogida(0);
						}
						else if (!azulCP2R && pMundo->getLLavesCogidas(0)){
							azulCP2R = true;
							pMundo->setLlaveCogida(0);
						}
						pMundo->setNivel(5);
						tipo = 152;
						pMundo->setPasoNivel(true);
						pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
						return true;
					}
				}
				else if (pMundo->getIndiceMapa() != 0 && pMundo->getIndiceMapa() != 12 && pMundo->getIndiceMapa() != 17){
					//para cuando es vertical, ponemos bien el collider
					if (pMundo->getIndiceMapa() == 6){
						felpudo = tileMap[indice]->getBox();
						felpudo.y = felpudo.y + 25;
						felpudo.h = felpudo.h - 15;
						felpudo.w = felpudo.w - 25;

						if (pMundo->checkCollision(box, felpudo)){
							pMundo->setNivel(5);
							tipo = 152;
							
							pMundo->setPasoNivel(true);
							pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
							return true;

						}
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
					pMundo->setNivel(-5);
					tipo = 151;
					pMundo->setPasoNivel(true);
					pMundo->setTextoArriba(true);
					if (pMundo->getIndiceMapa() == 12) {//ENTIENDO QUE ESTOY EN LA PLANTA 3
						pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 3", { 255, 255, 255, 1 }, *pMundo->getFuente());
					}
					if (pMundo->getIndiceMapa() == 17) {//ENTIENDO QUE ESTOY EN LA PLANTA 3
						pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 2", { 255, 255, 255, 1 }, *pMundo->getFuente());
					}
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
					return true;

				}

			}
			// PUERTA NARANJA
			else if ((tileMap[indice]->getType() == 157))
			{
				//Caso en el que la puerta esta cerrada, no tengo la llave necesaria
				if (pMundo->getIndiceMapa() == 0 && !pMundo->getLLavesCogidas(0) && !naranajaP5R){
					felpudo = tileMap[indice]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;
					if (pMundo->checkCollision(box, felpudo)){
						tipo = 158;
						pMundo->setPuertaCerrada(true);
						pMundo->getTexturaPCerrada()->loadFromText(pJuego->getRender(), "Cerrada.", { 255, 255, 255, 1 }, *pMundo->getFuente());
						pMundo->getPJ()->getResources()->getEfecto(3)->play(0);
						return true;

					}
					//Caso en el que no colisiono con la puerta
					else
						pMundo->setPuertaCerrada(false);
				}
				//planta 5 tiene q estar el baño abierto
				if ((pMundo->getLLavesCogidas(0) || naranajaP5R) && pMundo->getIndiceMapa() == 0 && azulCP5R){
					felpudo = tileMap[indice]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						//Por si tienes dos
						if (!naranajaP5R && pMundo->getLLavesCogidas(1)){
							naranajaP5R = true;
							pMundo->setLlaveCogida(0);
						}
						else if (!naranajaP5R && pMundo->getLLavesCogidas(0)){
							naranajaP5R = true;
							pMundo->setLlaveCogida(0);
						}
						pMundo->setNivel(6);
						tipo = 157;
						//Numero de planta
						pMundo->setTextoArriba(true);
						//Comprobacion de en que planta estoy actualmente 
						if (pMundo->getIndiceMapa() == 6) {//ENTIENDO QUE ESTOY EN LA PLANTA 4
							pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 4", { 255, 255, 255, 1 }, *pMundo->getFuente());
						}
						if (pMundo->getIndiceMapa() == 12) {//ENTIENDO QUE ESTOY EN LA PLANTA 3
							pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 3", { 255, 255, 255, 1 }, *pMundo->getFuente());
						}

						pMundo->setPasoNivel(true);
						pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
						return true;

					}
				}
				//planta 4
				if ((pMundo->getLLavesCogidas(0) || naranjaP4R) && pMundo->getIndiceMapa() == 6){
					felpudo = tileMap[indice]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						//Por si tienes dos
						if (!naranjaP4R && pMundo->getLLavesCogidas(1)){
							naranjaP4R = true;
							pMundo->setLlaveCogida(0);
						}
						else if (!naranjaP4R && pMundo->getLLavesCogidas(0)){
							naranjaP4R = true;
							pMundo->setLlaveCogida(0);
						}
						pMundo->setNivel(6);
						tipo = 157;
						//Numero de planta
						pMundo->setTextoArriba(true);
						//Comprobacion de en que planta estoy actualmente
						//BAJADA
						if (pMundo->getIndiceMapa() == 6) {//ENTIENDO QUE ESTOY EN LA PLANTA 4
							pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 4", { 255, 255, 255, 1 }, *pMundo->getFuente());
						}
						if (pMundo->getIndiceMapa() == 12) {//ENTIENDO QUE ESTOY EN LA PLANTA 3
							pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 3", { 255, 255, 255, 1 }, *pMundo->getFuente());
						}

						pMundo->setPasoNivel(true);
						pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
						return true;
					}
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
					pMundo->setNivel(-6);
					tipo = 174;
					pMundo->setTextoArriba(true);
					//Comprobacion de en que planta estoy actualmente 
					//SUBIDA
					if (pMundo->getIndiceMapa() == 0) {//ENTIENDO QUE ESTOY EN LA PLANTA 4
						pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 5", { 255, 255, 255, 1 }, *pMundo->getFuente());
					}
					if (pMundo->getIndiceMapa() == 6) {//ENTIENDO QUE ESTOY EN LA PLANTA 3
						pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 4", { 255, 255, 255, 1 }, *pMundo->getFuente());
					}


					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
					return true;

				}

			}
			// ESPEJO
			else if ((tileMap[indice]->getType() == 114))
			{
				//Aqui poner texto al llegar al baño

				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(24);
					pMundo->setCurapsj();
					tipo = 114;
					pMundo->setPasoNivel(true);
					pMundo->setMundo(Mundo_t::MOscuro);
					pMundo->getPJ()->getResources()->getEfecto(2)->play(0);
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
					pMundo->setNivel(-1);
					tipo = 495;
					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
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
					pMundo->setNivel(1);
					tipo = 500;
					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
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
					pMundo->setNivel(2);
					tipo = 499;
					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
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
					pMundo->setNivel(-2);
					tipo = 485;
					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
					return true;
				}
			}
			//PUERTA PISTACHO (OSCURO)
			else if ((tileMap[indice]->getType() == 503))
			{
				if ((pMundo->getLLavesCogidas(0) || pistachoP3O) && pMundo->getIndiceMapa() == 36){
					felpudo = tileMap[indice]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pMundo->setNivel(3);
						tipo = 157;
						pMundo->setPasoNivel(true);
						pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
						return true;
					}
				}
				else if (pMundo->getIndiceMapa() != 36){
					felpudo = tileMap[indice]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pMundo->setNivel(3);
						tipo = 157;
						pMundo->setPasoNivel(true);
						pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
						return true;
					}
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
					pMundo->setNivel(-4);
					tipo = 510;
					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
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
					pMundo->setNivel(4);
					tipo = 504;
					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
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
					pMundo->setNivel(-3);
					tipo = 498;
					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
					return true;

				}

			}
			//PUERTA AZUL CLARO (OSCURO)
			else if ((tileMap[indice]->getType() == 497))
			{
				//Si es vertical ponemos el collider bien
				if (pMundo->getIndiceMapa() == 24 || pMundo->getIndiceMapa() == 30){
					felpudo = tileMap[indice]->getBox();
					felpudo.y = felpudo.y + 25;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 25;

					if (pMundo->checkCollision(box, felpudo)){
						pMundo->setNivel(5);
						tipo = 497;
						pMundo->setPasoNivel(true);
						return true;

					}
				}				
				//Si es horizontal ponemos el collider bien
				else if(pMundo->getIndiceMapa() != 41 ){
					felpudo = tileMap[indice]->getBox();
					felpudo.y = felpudo.y - 5;
					felpudo.x = felpudo.x + 7;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 25;

					if (pMundo->checkCollision(box, felpudo)){
						pMundo->setNivel(5);
						tipo = 497;
						//Numero de planta
						pMundo->setTextoArriba(true);
						//Comprobacion de en que planta estoy actualmente 
						if (pMundo->getIndiceMapa() == 41) {//ENTIENDO QUE ESTOY EN LA PLANTA 4
							pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 2", { 255, 255, 255, 1 }, *pMundo->getFuente());
						}
						if (pMundo->getIndiceMapa() == 46) {//ENTIENDO QUE ESTOY EN LA PLANTA 3
							pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 1", { 255, 255, 255, 1 }, *pMundo->getFuente());
						}
						pMundo->setPasoNivel(true);
						pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
						return true;

					}
				}

			}
			// PUERTA VERDE (OSCURO)
			else if ((tileMap[indice]->getType() == 496) && pMundo->getIndiceMapa() != 46)
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(-5);
					tipo = 496;
					//pMundo->setTextoArriba(true);
					if (pMundo->getIndiceMapa() == 36) {//ENTIENDO QUE ESTOY EN LA PLANTA 3
						pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 3", { 255, 255, 255, 1 }, *pMundo->getFuente());
					}
					if (pMundo->getIndiceMapa() == 41) {//ENTIENDO QUE ESTOY EN LA PLANTA 2
						pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 2", { 255, 255, 255, 1 }, *pMundo->getFuente());
					}
					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
					return true;

				}

			}
			// PUERTA NARANJA (OSCURO)
			else if (tileMap[indice]->getType() == 502)
			{
				if ((pMundo->getIndiceMapa() == 24 && naranajaP5R) || (pMundo->getIndiceMapa() != 24 && pMundo->getIndiceMapa() != 30)){
					felpudo = tileMap[indice]->getBox();
					felpudo.x = felpudo.x + 10;
					felpudo.h = felpudo.h - 15;
					felpudo.w = felpudo.w - 20;

					if (pMundo->checkCollision(box, felpudo)){
						pMundo->setNivel(6);
						tipo = 502;
						pMundo->setTextoArriba(true);
						//Comprobacion de en que planta estoy actualmente 
						if (pMundo->getIndiceMapa() == 30) {//ENTIENDO QUE ESTOY EN LA PLANTA 4
							pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 4", { 255, 255, 255, 1 }, *pMundo->getFuente());
						}
						if (pMundo->getIndiceMapa() == 36) {//ENTIENDO QUE ESTOY EN LA PLANTA 3
							pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 3", { 255, 255, 255, 1 }, *pMundo->getFuente());
						}
						pMundo->setPasoNivel(true);
						pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
						return true;

					}
				}

			}
			// PUERTA GRIS OSCURO (OSCURO)
			else if (tileMap[indice]->getType() == 519 && pMundo->getIndiceMapa() != 36)
			{
				felpudo = tileMap[indice]->getBox();
				felpudo.x = felpudo.x + 10;
				felpudo.h = felpudo.h - 15;
				felpudo.w = felpudo.w - 20;

				if (pMundo->checkCollision(box, felpudo)){
					pMundo->setNivel(-6);
					tipo = 519;
					pMundo->setTextoArriba(true);
					//Comprobacion de en que planta estoy actualmente 
					if (pMundo->getIndiceMapa() == 24) {//ENTIENDO QUE ESTOY EN LA PLANTA 4
						pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 5", { 255, 255, 255, 1 }, *pMundo->getFuente());
					}
					if (pMundo->getIndiceMapa() == 30) {//ENTIENDO QUE ESTOY EN LA PLANTA 3
						pMundo->getTextura()->loadFromText(pJuego->getRender(), "PLANTA 4", { 255, 255, 255, 1 }, *pMundo->getFuente());
					}
					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(1)->play(0);
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
					pMundo->setNivel(-24);
					pMundo->setCurapsj();
					tipo = 459;
					pMundo->setMundo(Mundo_t::MReal);
					pMundo->setPasoNivel(true);
					pMundo->getPJ()->getResources()->getEfecto(2)->play(0);
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
				&& tileMap[indice]->getType() != 57
				&& tileMap[indice]->getType() != 58
				&& tileMap[indice]->getType() != 59
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
				&& tileMap[indice]->getType() != 281
				&& tileMap[indice]->getType() != 282
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
				&& tileMap[indice]->getType() != 402
				&& tileMap[indice]->getType() != 403
				&& tileMap[indice]->getType() != 404
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
				&& tileMap[indice]->getType() != 626
				&& tileMap[indice]->getType() != 627
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
