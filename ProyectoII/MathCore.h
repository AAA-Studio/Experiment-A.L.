#ifndef _H_MathCore_H_
#define _H_MathCore_H_

class Vector2
{
public:
	Vector2();
	Vector2(float _x, float _y);

//private:
	float m_x;
	float m_y;
};

class Vector3
{
public:
	Vector3();
	Vector3(float _x, float _y, float _z);

//private:
	float m_x;
	float m_y;
	float m_z;
};

class MathCore
{
public:
	MathCore();
	~MathCore();
};
#endif
