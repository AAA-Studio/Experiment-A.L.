#ifndef _H_Rectangle_H_
#define _H_Rectangle_H_
class Rectangle
{
public:
	Rectangle(){
		m_left = m_right = m_top = m_bottom = m_width = m_height = 0.0f;
	}
	Rectangle(float _left, float _top, float _width, float _height) : 
		m_left(_left), m_right(m_left + _width), m_top(_top), m_bottom(m_top + _height), m_width(_width), m_height(_height) {
	}
	~Rectangle();

	float GetLeft() { return m_left; }
	float GetRight(){ return m_right; }
	float GetTop(){ return m_top; }
	float GetBottom(){ return m_bottom; }
	float GetWidth(){ return m_width; }
	float GetHeight(){ return m_height; }

private: 
	float m_left;
	float m_right;
	float m_top;
	float m_bottom;
	float m_width;
	float m_height;

};
#endif

