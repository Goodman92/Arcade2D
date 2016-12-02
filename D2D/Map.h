#pragma once
#include "Tilegenerator.h"

int jee[7][9] =
{
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 0, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

class Map {

public:
	Map(float x, float y, PCWSTR img);
	inline float getHorizontalPosition();
	inline float getVerticalPosition();
	inline PCWSTR getBgImage();
	void setHorizontalPosition(float x);
	void setVerticalPosition(float y);
	void setRect(RECT r);
	void scroll();
	bool isScrolling;

	std::vector<std::vector<float>> getTilePositions() {
		return m_tilePositions;
	}
	void initializeTiles();

private:
	std::vector<int> tileZ;
	RECT m_windowRect;
	float m_x;
	float m_y;

	float m_mapWidth;
	float m_mapHeight;
	
	float scrollDirection;
	Tilegenerator m_tilegenerator;
	PCWSTR m_backgroundImage;
	std::vector<std::vector<float>> m_tilePositions;
};

void Map::setRect(RECT r) {
	m_windowRect = r;
	initializeTiles();
}

Map::Map(float x = 0, float y = 0, PCWSTR img = L"") {
	m_x = x;
	m_y = y;
	m_backgroundImage = img;	
}

// korjaa kunnolliseks
void Map::initializeTiles() {
	m_tilePositions.clear();
	LONG width = m_windowRect.right - m_windowRect.left;
	LONG height = m_windowRect.bottom - m_windowRect.top;

	auto horizontalTilesCount = width / 70;
	auto verticalTilesCount = height / 70;

	int w = 70;
	int h = 70;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 9; j++) {
			if (i * h < m_y + 480) {
				if (j * w < m_x + 640 && j*w + w >= m_x) {
					if(jee[i][j] == 1) {
						float xval = j*w - m_x <=  0 ? 0 : j*w - m_x;
						float xwit = xval <= 0 ? w + j * w - m_x : w;
						std::vector<float> v;
						v.push_back(xval);
						v.push_back(i * h);
						v.push_back(xwit);
						v.push_back(m_x);
						m_tilePositions.push_back(v);
					}
				}
			}
		}
	}


}
//mappi kolminkertasena
void Map::scroll() {
	if(isScrolling) {
		if (m_x + scrollDirection > 2044) {
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