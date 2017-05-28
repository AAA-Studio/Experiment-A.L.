#include "RecursosSDL.h"
#include "JuegoSDL.h"

RecursosSDL::RecursosSDL(JuegoSDL* game) :
	game_(game), numOfTextures_(0), textures_(nullptr), numOfFonts_(0), fonts_(
	nullptr), numOfMusic_(0), music_(nullptr), numOfSoundEffects_(
	0), soundEffects_(nullptr) {
}

void RecursosSDL::setTextures(std::vector<std::string> textures) {
	closeTextures();
	numOfTextures_ = textures.size();
	textures_ = new TexturasSDL*[numOfTextures_];
	for (int i = 0; i < numOfTextures_; i++) {
		textures_[i] = new TexturasSDL(game_->getRender(), textures[i]);
	}
}

void RecursosSDL::setFonts(std::vector<std::string> fonts) {
	closeFonts();
	numOfFonts_ = fonts.size();
	fonts_ = new Fuente*[numOfFonts_];
	for (int i = 0; i < numOfFonts_; i++) {
		fonts_[i] = new Fuente(fonts[i],20);
	}
}

void RecursosSDL::setMusic(std::vector<std::string> music) {
	closeMusic();
	numOfMusic_ = music.size();
	music_ = new Musica*[numOfMusic_];
	for (int i = 0; i < numOfMusic_; i++) {
		music_[i] = new Musica(music[i]);
	}
}

void RecursosSDL::setSoundEffects(std::vector<std::string> soundEffects) {
	closeSoundEffects();
	numOfSoundEffects_ = soundEffects.size();
	soundEffects_ = new Efecto*[numOfSoundEffects_];
	for (int i = 0; i < numOfSoundEffects_; i++) {
		soundEffects_[i] = new Efecto(soundEffects[i]);
	}
}

RecursosSDL::~RecursosSDL() {
	closeTextures();
	closeFonts();
	closeMusic();
	closeSoundEffects();
}

void RecursosSDL::closeTextures() {
	for (int i = 0; i < numOfTextures_; i++) {
		if (textures_[i] != nullptr) {
			delete textures_[i];
		}
	}
	delete[] textures_;
	numOfTextures_ = 0;

}

void RecursosSDL::closeFonts() {
	for (int i = 0; i < numOfFonts_; i++) {
		if (fonts_[i] != nullptr) {
			delete fonts_[i];
		}
	}
	delete[] fonts_;
	numOfFonts_ = 0;
}

void RecursosSDL::closeMusic() {
	for (int i = 0; i < numOfMusic_; i++) {
		if (music_[i] != nullptr) {
			delete music_[i];
		}
	}
	delete[] music_;
	numOfMusic_ = 0;
}

void RecursosSDL::closeSoundEffects() {
	for (int i = 0; i < numOfSoundEffects_; i++) {
		if (soundEffects_[i] != nullptr) {
			delete soundEffects_[i];
		}
	}
	delete[] soundEffects_;
	numOfSoundEffects_ = 0;
}

TexturasSDL* RecursosSDL::getTextura(int i) const {
	if (i < numOfTextures_)
		return textures_[i];
	else
		return nullptr;
}

Fuente* RecursosSDL::getFuente(int i) const {
	if (i < numOfFonts_)
		return fonts_[i];
	else
		return nullptr;
}

Musica* RecursosSDL::getMusica(int i) const {
	if (i < numOfMusic_)
		return music_[i];
	else
		return nullptr;
}

Efecto* RecursosSDL::getEfecto(int i) const {
	if (i < numOfSoundEffects_)
		return soundEffects_[i];
	else
		return nullptr;
}

