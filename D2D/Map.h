#pragma once

int jee[7][9] =
{
	{ 0, 0, 0, 1, 1, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};


class Map : public GameComponent {

public:
	Map(float x, float y, PCWSTR img);
	inline ComponentPlacement getDimensions();
	void setHorizontalPosition(float x);
	void setVerticalPosition(float y);
	void setRect(RECT r);
	void scroll();
	void animate();
	bool isScrolling;
	PCWSTR getImage();
	PCWSTR getTileImage();
	bool hasTile(int y, int x) {
		if (y > 7) {
			return false;
		}
		else if (x > 9) {
			return false;
		}
		else

		return jee[y][x];
	}

	std::vector<std::vector<float>> getTilePositions() {
		return m_tilePositions;
	}

	void initializeTiles();
	ComponentPlacement m_placement;
private:
	RECT m_windowRect;
	float m_x;
	float m_y;
	Dimensions dim;
	float m_mapWidth;
	float m_mapHeight;
	float scrollDirection;
	PCWSTR m_backgroundImage;
	std::vector<std::vector<float>> m_tilePositions;
};

void Map::animate() {
	initializeTiles();
}

ComponentPlacement Map::getDimensions() {
	return m_placement;
}
void Map::setRect(RECT r) {
	m_windowRect = r;
	initializeTiles();
}

Map::Map(float x = 0, float y = 0, PCWSTR img = L"") {
	m_x = x;
	m_y = y;
	m_backgroundImage = img;	
	
	m_placement.x = x;
	m_placement.y = y;
	m_placement.m_xw = 640;
	m_placement.m_yh = 490;
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
			if (i * h < m_y + height) {
				if (j * w < m_x + width && j*w + w >= m_x) {
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
			m_placement.m_x = 0;
		}
		if (m_x + scrollDirection <= 0) {
			m_x = 0;
			m_placement.m_x = 0;
		}
		else {
			m_x += scrollDirection;
			m_placement.m_x += scrollDirection;
		}
	}
}

void Map::setHorizontalPosition(float x) {
	scrollDirection = x;
	isScrolling = true;
	scroll();
}

void Map::setVerticalPosition(float y) {
	scrollDirection = y;
	isScrolling = true;
}

PCWSTR Map::getImage() {
	return m_backgroundImage;
}

PCWSTR Map::getTileImage() {
	return L"tiles_spritesheet.png";
}