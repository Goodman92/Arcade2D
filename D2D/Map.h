#pragma once
#include "Tilegenerator.h"
class Map {

public:
	Map(float x, float y, PCWSTR img);
	inline float getHorizontalPosition();
	inline float getVerticalPosition();
	inline PCWSTR getBgImage();
	void setHorizontalPosition(float x);
	void setVerticalPosition(float y);
	void scroll();
	bool isScrolling;
private:
	float m_x;
	float m_y;
	float scrollDirection;
	Tilegenerator m_tilegenerator;
	PCWSTR m_backgroundImage;
};

Map::Map(float x = 0, float y = 0, PCWSTR img = L"") {
	m_x = x;
	m_y = y;
	m_backgroundImage = img;
}

// korjaa kunnolliseks
void Map::scroll() {
	if(isScrolling) {
		if (m_x + scrollDirection > 1000) {
			m_x = 0;
		}
		if (m_x + scrollDirection <= 0) {
			m_x = 0;
		}
		else {
			m_x += scrollDirection;
		}
	}
}

void Map::setHorizontalPosition(float x) {
	scrollDirection = x;
	isScrolling = true;
}

void Map::setVerticalPosition(float y) {
	scrollDirection = y;
	isScrolling = true;
}

float Map::getHorizontalPosition() {
	return m_x;
}

float Map::getVerticalPosition() {
	return m_y;
}

PCWSTR Map::getBgImage() {
	return m_backgroundImage;
}