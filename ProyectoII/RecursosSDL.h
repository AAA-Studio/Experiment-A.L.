
#ifndef RECURSOSSDL_H_
#define RECURSOSSDL_H_

#include "TexturasSDL.h"
#include "Fuente.h"
#include "Musica.h"
#include <vector>

class JuegoSDL;
class RecursosSDL {
public:
	RecursosSDL(JuegoSDL* game);
	virtual ~RecursosSDL();

	void setTextures(std::vector<std::string> textures);
	void setFonts(std::vector<std::string> fonts);
	void setMusic(std::vector<std::string> music);
	void setSoundEffects(std::vector<std::string> soundEffects);

	TexturasSDL* getTextura(int i) const;
	Fuente* getFuente(int i) const;
	Musica* getMusica(int i) const;
	Efecto* getEfecto(int i) const;

private:
	void closeTextures();
	void closeFonts();
	void closeMusic();
	void closeSoundEffects();

	JuegoSDL* game_;

	int numOfTextures_;
	TexturasSDL** textures_;

	int numOfFonts_;
	Fuente** fonts_;

	int numOfMusic_;
	Musica** music_;

	int numOfSoundEffects_;
	Efecto** soundEffects_;
};

#endif /* RECURSOSSDL_H_ */
