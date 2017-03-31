#ifndef Juego_H
#define Juego_H
#include "checkML.h"
#include "EstadoJuego.h"
#include "TexturasSDL.h"
#include "Fuente.h"
#include "Musica.h"
#include <vector>
#include <string>
#include <SDL.h>

using namespace std;

//-----------------CONSTANTES----------------------

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;
//The dimensions of the level
const int LEVEL_WIDTH = 800;
const int LEVEL_HEIGHT = 640;

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES = 500;
const int TOTAL_TILE_SPRITES = 390;

//The different tile sprites
const int TILE_0 = 0;
const int TILE_1 = 1;
const int TILE_2 = 2;
const int TILE_3 = 3;
const int TILE_4 = 4;
const int TILE_5 = 5;
const int TILE_6 = 6;
const int TILE_7 = 7;
const int TILE_8 = 8;
const int TILE_9 = 9;
const int TILE_10 = 10;
const int TILE_11 = 11;
const int TILE_12 = 12;
const int TILE_13 = 13;
const int TILE_14 = 14;
const int TILE_15 = 15;
const int TILE_16 = 16;
const int TILE_17 = 17;
const int TILE_18 = 18;
const int TILE_19 = 19;
const int TILE_20 = 20;
const int TILE_21 = 21;
const int TILE_22 = 22;
const int TILE_23 = 23;
const int TILE_24 = 24;
const int TILE_25 = 25;
const int TILE_26 = 26;
const int TILE_27 = 27;
const int TILE_28 = 28;
const int TILE_29 = 29;
const int TILE_30 = 30;
const int TILE_31 = 31;
const int TILE_32 = 32;
const int TILE_33 = 33;
const int TILE_34 = 34;
const int TILE_35 = 35;
const int TILE_36 = 36;
const int TILE_37 = 37;
const int TILE_38 = 38;
const int TILE_39 = 39;
const int TILE_40 = 40;
const int TILE_41 = 41;
const int TILE_42 = 42;
const int TILE_43 = 43;
const int TILE_44 = 44;
const int TILE_45 = 45;
const int TILE_46 = 46;
const int TILE_47 = 47;
const int TILE_48 = 48;
const int TILE_49 = 49;
const int TILE_50 = 50;
const int TILE_51 = 51;
const int TILE_52 = 52;
const int TILE_53 = 53;
const int TILE_54 = 54;
const int TILE_55 = 55;
const int TILE_56 = 56;
const int TILE_57 = 57;
const int TILE_58 = 58;
const int TILE_59 = 59;
const int TILE_60 = 60;
const int TILE_61 = 61;
const int TILE_62 = 62;
const int TILE_63 = 63;
const int TILE_64 = 64;
const int TILE_65 = 65;
const int TILE_66 = 66;
const int TILE_67 = 67;
const int TILE_68 = 68;
const int TILE_69 = 69;
const int TILE_70 = 70;
const int TILE_71 = 71;
const int TILE_72 = 72;
const int TILE_73 = 73;
const int TILE_74 = 74;
const int TILE_75 = 75;
const int TILE_76 = 76;
const int TILE_77 = 77;
const int TILE_78 = 78;
const int TILE_79 = 79;
const int TILE_80 = 80;
const int TILE_81 = 81;
const int TILE_82 = 82;
const int TILE_83 = 83;
const int TILE_84 = 84;
const int TILE_85 = 85;
const int TILE_86 = 86;
const int TILE_87 = 87;
const int TILE_88 = 88;
const int TILE_89 = 89;
const int TILE_90 = 90;
const int TILE_91 = 91;
const int TILE_92 = 92;
const int TILE_93 = 93;
const int TILE_94 = 94;
const int TILE_95 = 95;
const int TILE_96 = 96;
const int TILE_97 = 97;
const int TILE_98 = 98;
const int TILE_99 = 99;
const int TILE_100 = 100;
const int TILE_101 = 101;
const int TILE_102 = 102;
const int TILE_103 = 103;
const int TILE_104 = 104;
const int TILE_105 = 105;
const int TILE_106 = 106;
const int TILE_107 = 107;
const int TILE_108 = 108;
const int TILE_109 = 109;
const int TILE_110 = 110;
const int TILE_111 = 111;
const int TILE_112 = 112;
const int TILE_113 = 113;
const int TILE_114 = 114;
const int TILE_115 = 115;
const int TILE_116 = 116;
const int TILE_117 = 117;
const int TILE_118 = 118;
const int TILE_119 = 119;
const int TILE_120 = 120;
const int TILE_121 = 121;
const int TILE_122 = 122;
const int TILE_123 = 123;
const int TILE_124 = 124;
const int TILE_125 = 125;
const int TILE_126 = 126;
const int TILE_127 = 127;
const int TILE_128 = 128;
const int TILE_129 = 129;
const int TILE_130 = 130;
const int TILE_131 = 131;
const int TILE_132 = 132;
const int TILE_133 = 133;
const int TILE_134 = 134;
const int TILE_135 = 135;
const int TILE_136 = 136;
const int TILE_137 = 137;
const int TILE_138 = 138;
const int TILE_139 = 139;
const int TILE_140 = 140;
const int TILE_141 = 141;
const int TILE_142 = 142;
const int TILE_143 = 143;
const int TILE_144 = 144;
const int TILE_145 = 145;
const int TILE_146 = 146;
const int TILE_147 = 147;
const int TILE_148 = 148;
const int TILE_149 = 149;
const int TILE_150 = 150;
const int TILE_151 = 151;
const int TILE_152 = 152;
const int TILE_153 = 153;
const int TILE_154 = 154;
const int TILE_155 = 155;
const int TILE_156 = 156;
const int TILE_157 = 157;
const int TILE_158 = 158;
const int TILE_159 = 159;
const int TILE_160 = 160;
const int TILE_161 = 161;
const int TILE_162 = 162;
const int TILE_163 = 163;
const int TILE_164 = 164;
const int TILE_165 = 165;
const int TILE_166 = 166;
const int TILE_167 = 167;
const int TILE_168 = 168;
const int TILE_169 = 169;
const int TILE_170 = 170;
const int TILE_171 = 171;
const int TILE_172 = 172;
const int TILE_173 = 173;
const int TILE_174 = 174;
const int TILE_175 = 175;
const int TILE_176 = 176;
const int TILE_177 = 177;
const int TILE_178 = 178;
const int TILE_179 = 179;
const int TILE_180 = 180;
const int TILE_181 = 181;
const int TILE_182 = 182;
const int TILE_183 = 183;
const int TILE_184 = 184;
const int TILE_185 = 185;
const int TILE_186 = 186;
const int TILE_187 = 187;
const int TILE_188 = 188;
const int TILE_189 = 189;
const int TILE_190 = 190;
const int TILE_191 = 191;
const int TILE_192 = 192;
const int TILE_193 = 193;
const int TILE_194 = 194;
const int TILE_195 = 195;
const int TILE_196 = 196;
const int TILE_197 = 197;
const int TILE_198 = 198;
const int TILE_199 = 199;
const int TILE_200 = 200;
const int TILE_201 = 201;
const int TILE_202 = 202;
const int TILE_203 = 203;
const int TILE_204 = 204;
const int TILE_205 = 205;
const int TILE_206 = 206;
const int TILE_207 = 207;
const int TILE_208 = 208;
const int TILE_209 = 209;
const int TILE_210 = 210;
const int TILE_211 = 211;
const int TILE_212 = 212;
const int TILE_213 = 213;
const int TILE_214 = 214;
const int TILE_215 = 215;
const int TILE_216 = 216;
const int TILE_217 = 217;
const int TILE_218 = 218;
const int TILE_219 = 219;
const int TILE_220 = 220;
const int TILE_221 = 221;
const int TILE_222 = 222;
const int TILE_223 = 223;
const int TILE_224 = 224;
const int TILE_225 = 225;
const int TILE_226 = 226;
const int TILE_227 = 227;
const int TILE_228 = 228;
const int TILE_229 = 229;
const int TILE_230 = 230;
const int TILE_231 = 231;
const int TILE_232 = 232;
const int TILE_233 = 233;
const int TILE_234 = 234;
const int TILE_235 = 235;
const int TILE_236 = 236;
const int TILE_237 = 237;
const int TILE_238 = 238;
const int TILE_239 = 239;
const int TILE_240 = 240;
const int TILE_241 = 241;
const int TILE_242 = 242;
const int TILE_243 = 243;
const int TILE_244 = 244;
const int TILE_245 = 245;
const int TILE_246 = 246;
const int TILE_247 = 247;
const int TILE_248 = 248;
const int TILE_249 = 249;
const int TILE_250 = 250;
const int TILE_251 = 251;
const int TILE_252 = 252;
const int TILE_253 = 253;
const int TILE_254 = 254;
const int TILE_255 = 255;
const int TILE_256 = 256;
const int TILE_257 = 257;
const int TILE_258 = 258;
const int TILE_259 = 259;
const int TILE_260 = 260;
const int TILE_261 = 261;
const int TILE_262 = 262;
const int TILE_263 = 263;
const int TILE_264 = 264;
const int TILE_265 = 265;
const int TILE_266 = 266;
const int TILE_267 = 267;
const int TILE_268 = 268;
const int TILE_269 = 269;
const int TILE_270 = 270;
const int TILE_271 = 271;
const int TILE_272 = 272;
const int TILE_273 = 273;
const int TILE_274 = 274;
const int TILE_275 = 275;
const int TILE_276 = 276;
const int TILE_277 = 277;
const int TILE_278 = 278;
const int TILE_279 = 279;
const int TILE_280 = 280;
const int TILE_281 = 281;
const int TILE_282 = 282;
const int TILE_283 = 283;
const int TILE_284 = 284;
const int TILE_285 = 285;
const int TILE_286 = 286;
const int TILE_287 = 287;
const int TILE_288 = 288;
const int TILE_289 = 289;
const int TILE_290 = 290;
const int TILE_291 = 291;
const int TILE_292 = 292;
const int TILE_293 = 293;
const int TILE_294 = 294;
const int TILE_295 = 295;
const int TILE_296 = 296;
const int TILE_297 = 297;
const int TILE_298 = 298;
const int TILE_299 = 299;
const int TILE_300 = 300;
const int TILE_301 = 301;
const int TILE_302 = 302;
const int TILE_303 = 303;
const int TILE_304 = 304;
const int TILE_305 = 305;
const int TILE_306 = 306;
const int TILE_307 = 307;
const int TILE_308 = 308;
const int TILE_309 = 309;
const int TILE_310 = 310;
const int TILE_311 = 311;
const int TILE_312 = 312;
const int TILE_313 = 313;
const int TILE_314 = 314;
const int TILE_315 = 315;
const int TILE_316 = 316;
const int TILE_317 = 317;
const int TILE_318 = 318;
const int TILE_319 = 319;
const int TILE_320 = 320;
const int TILE_321 = 321;
const int TILE_322 = 322;
const int TILE_323 = 323;
const int TILE_324 = 324;
const int TILE_325 = 325;
const int TILE_326 = 326;
const int TILE_327 = 327;
const int TILE_328 = 328;
const int TILE_329 = 329;
const int TILE_330 = 330;
const int TILE_331 = 331;
const int TILE_332 = 332;
const int TILE_333 = 333;
const int TILE_334 = 334;
const int TILE_335 = 335;
const int TILE_336 = 336;
const int TILE_337 = 337;
const int TILE_338 = 338;
const int TILE_339 = 339;
const int TILE_340 = 340;
const int TILE_341 = 341;
const int TILE_342 = 342;
const int TILE_343 = 343;
const int TILE_344 = 344;
const int TILE_345 = 345;
const int TILE_346 = 346;
const int TILE_347 = 347;
const int TILE_348 = 348;
const int TILE_349 = 349;
const int TILE_350 = 350;
const int TILE_351 = 351;
const int TILE_352 = 352;
const int TILE_353 = 353;
const int TILE_354 = 354;
const int TILE_355 = 355;
const int TILE_356 = 356;
const int TILE_357 = 357;
const int TILE_358 = 358;
const int TILE_359 = 359;
const int TILE_360 = 360;
const int TILE_361 = 361;
const int TILE_362 = 362;
const int TILE_363 = 363;
const int TILE_364 = 364;
const int TILE_365 = 365;
const int TILE_366 = 366;
const int TILE_367 = 367;
const int TILE_368 = 368;
const int TILE_369 = 369;
const int TILE_370 = 370;
const int TILE_371 = 371;
const int TILE_372 = 372;
const int TILE_373 = 373;
const int TILE_374 = 374;
const int TILE_375 = 375;
const int TILE_376 = 376;
const int TILE_377 = 377;
const int TILE_378 = 378;
const int TILE_379 = 379;
const int TILE_380 = 380;
const int TILE_381 = 381;
const int TILE_382 = 382;
const int TILE_383 = 383;
const int TILE_384 = 384;
const int TILE_385 = 385;
const int TILE_386 = 386;
const int TILE_387 = 387;
const int TILE_388 = 388;
const int TILE_389 = 389;


//----------------------------------------------------


//------------------ENUMS--------------------------

enum  Texturas_t{ TJugador, TPlay, TMenu, TExit, TTilemap,/*TFondoMenu,*/ TFuente, Texturas_t_SIZE };
enum  Efectos_t{ ENull, Efectos_t_SIZE };
enum  Musica_t{ Musica_t_SIZE};
enum Estados_t{MInicio,MGameOver,MPausa,MundoReal,MundoOscuro};

//----------------------------------------------------


class Juego
{
public:
	//Constructora, en caso de error muestra un mensaje y deja los atributos nulos y hace un thwrow que se captura en main
	Juego();
	//Destructora
	~Juego();

	// Arranca el bucle principal y, si se termina el juego. Tambien puede terminar si se cierra la ventana
	void run();

	//----------------ESTADOS---------------------

	//Devuelve el estado actual
	inline EstadoJuego * topEstado(){ return vectorEstados[vectorEstados.size() - 1]; };

	void changeState(EstadoJuego *estado);

	//Elimina el último estado
	void popState();

	// en duda
	void goToPausa(EstadoJuego * estado);

	//Sale del programa
	void setSalir(){ exit = true; };
	
	void setNivel(int i){ nivel =  i; };
	//---------------GETTER----------------------
	//Saber el nivel del mapa en el que estamos
	int getNivel() { return nivel; };
	//Detecta posición del raton
	void getMousePos(int & mpx, int & mpy) const;

	//Dibujado
	inline SDL_Renderer * getRender() const{ return pRenderer; };
	inline TexturasSDL * getTextura(Texturas_t et) const { return texturas[et]; }

	//Musica
	inline Efecto * getEfecto(Efectos_t et) const { return efectos[et]; }
	//Musica * getMusica(Musica_t et) const { return musica[et]; }

	//Fuente
	inline Fuente getFuente() const { return fuente; }

	//Ventana
	inline int getAncho(){ return winRect.w; }
	inline int getAlto(){ return winRect.h; }

	//-----------TILE----------------

	SDL_Rect gTileClips[TOTAL_TILE_SPRITES]; //Array con los rectángulos de las colisiones

	inline SDL_Rect getRectTile(int numTile){ return gTileClips[numTile]; };//Devuelve la colision del tile pasado como parametro

	void recortarTiles();

	//---------------------------------------

	bool borraEstado;
	Estados_t estadoEnum;

	void gestionaEstados(Estados_t estado);

	string SelectorDeNiveles();
	int indiceMapas=1;
private:

	//Atributos
	int nivel;
	bool exit;
	int posMouseX, posMouseY;
	vector <string> nombreMapas;
	

	SDL_Window *pWin;//Puntero de la ventana
	SDL_Renderer *pRenderer;//Puntero del renderizador

	SDL_Rect winRect;//Rectángulo de la ventana
	SDL_Color colorWin;//Color de la ventana

	vector <EstadoJuego*> vectorEstados;

	TexturasSDL*  texturas[Texturas_t_SIZE];

	//AMPLIACIONES
	Fuente fuente;
	TexturasSDL * textFuente;

	//Musica * musica[Musica_t_SIZE];
	Efecto * efectos[Efectos_t_SIZE];

	//Inicializa el renderizador, en caso de error muestra un mensaje y deja los atributos nulos
	void initSDL();
	//Libera los atributos inicados en initSDL
	void closeSDL();

	void initMedia();
	void freeMedia();

	void render();

	// REVISAR
	void handle_event();

	//Añade un nuevo estado
	void pushState(EstadoJuego * nuevoEstado);

};

#endif