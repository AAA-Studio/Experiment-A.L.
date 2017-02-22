#pragma once
class ObjetosJuego
{
public:

	ObjetosJuego()
	{
	}
	virtual void dibujar() = 0;
	virtual void coger() = 0;
	virtual void soltar() = 0;

	virtual ~ObjetosJuego()
	{
	}
};

