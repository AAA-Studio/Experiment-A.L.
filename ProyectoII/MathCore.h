#ifndef _H_MathCore_H_
#define _H_MathCore_H_
#include <iostream>
using namespace std;
template <class T>
class Vector2
{
public:
	Vector2(){ m_x = m_y = 0.0f; }
	Vector2(float _x, float _y) : m_x(_x), m_y(_y);
	~Vector2();

	Vector2 Vector2::operator - (const Vector2 &v1, const Vector2 &v2) {
		return Vector2(v1.m_x - v2.m_x, v1.m_y - v2.m_y);
		//return *(new Vector2(v1.m_x - v2.m_x, v1.m_y - v2.m_y));
	}

	float m_x;
	float m_y;
	float Length = sqrt((x*x) + (y*y));
};

// template <class T>
class Vector3
{
public:
	Vector3(){ m_x = m_y = m_z = 0.0f; }
	Vector3(float _x, float _y, float _z) : m_x(_x), m_y(_y), m_z(_z){}
	~Vector3();

	//Vector3& Vector3::operator - (const Vector3 &v1, const Vector3 &v2) {
	Vector3 Vector3::operator- (const Vector3 &v2) {
		//return *(new Vector3(v1.m_x - v2.m_x, v1.m_y - v2.m_y, v1.m_z - v2.m_z));
		return Vector3(m_x - v2.m_x, m_y - v2.m_y, m_z - v2.m_z);
	}

	float m_x;
	float m_y;
	float m_z;
	float Length; // = sqrt((x*x) + (y*y) + (z*z));
};

class MathCore
{
public:
	MathCore();
	~MathCore();
};
#endif
