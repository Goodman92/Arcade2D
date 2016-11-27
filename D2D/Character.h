#pragma once

struct Dimensions {
	Dimensions() {
		m_x = m_xw = m_y = m_yh = 0.0f;
	}
	float m_x;
	float m_y;
	float m_xw;
	float m_yh;
};

class Character {
public:
	Character(PCWSTR img);
	inline float getX();
	inline float getY();
	inline float getXW();
	inline float getYH();
	inline PCWSTR getImg();
	void animate();
	void setX(float x);
	void setY(float y);
	void setDim(float x, float y, float xw, float yh);
	float x, y;
private:
	Dimensions dim;
	PCWSTR m_image;
};

void Character::setDim(float x, float y, float xw, float yh) {
	dim.m_x = x;
	dim.m_xw = xw;
	dim.m_y = y;
	dim.m_yh = yh;
}

Character::Character(PCWSTR img = L"") {
	x = y = 0.0f;
	m_image = img;
}

float Character::getX() {
	return dim.m_x;
}

float Character::getY() {
	return dim.m_y;
}

float Character::getXW() {
	return dim.m_xw;
}

float Character::getYH() {
	return dim.m_yh;
}

PCWSTR Character::getImg() {
	return m_image;
}

void Character::setX(float x) {
	dim.m_x = x;
}

void Character::setY(float y) {
	dim.m_y = y;
}