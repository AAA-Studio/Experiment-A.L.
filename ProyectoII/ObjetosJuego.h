#pragma once
class ObjetosJuego
{
public:

	ObjetosJuego()
	{
	}
	virtual void dibujar() = 0;
	virtual void coger() = 0;
	virtual void soltar(int px, int py) = 0;

	virtual ~ObjetosJuego()
	{
	}
};

