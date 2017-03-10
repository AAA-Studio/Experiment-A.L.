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

	inline float GetLeft() const { return m_left; }
	inline float GetRight() const { return m_right; }
	inline float GetTop() const { return m_top; }
	inline float GetBottom() const { return m_bottom; }
	inline float GetWidth() const { return m_width; }
	inline float GetHeight() const { return m_height; }

private: 
	float m_left;
	float m_right;
	float m_top;
	float m_bottom;
	float m_width;
	float m_height;

};
#endif

