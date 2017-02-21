#ifndef Error_H
#define Error_H

#include <string>

using namespace std;

//Para las excepciones que lanzará el juego al iniciarse
class Error
{
public:
	Error(string const & mensaje) : mensajeError(mensaje){};
	virtual ~Error(){};

	const string& mensaje() const{ return mensajeError; }

protected:
	string mensajeError;
};

class ErrorImagen : public Error
{
public:
	ErrorImagen(string const & mensaje) : Error(mensaje){};
	virtual ~ErrorImagen(){};
};

class ErrorSonido : public Error
{
public:
	ErrorSonido(string const & mensaje) : Error(mensaje){};
	virtual ~ErrorSonido(){};
};

class ErrorFuente : public Error
{
public:
	ErrorFuente(string const & mensaje) : Error(mensaje){};
	virtual ~ErrorFuente(){};
};

#endif