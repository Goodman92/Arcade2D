#pragma once

class Character : public GameComponent {
public:
	Character(PCWSTR img);
	inline ComponentPlacement getDimensions();
	PCWSTR getImage();
	virtual void animate() = 0;
	void setDim(float x, float y, float xw, float yh);
	float x, y;
	ComponentPlacement m_placement;
private:
	Dimensions dim;
	PCWSTR m_image;
};

ComponentPlacement Character::getDimensions() {
	return m_placement;
}

void Character::setDim(float x, float y, float xw, float yh) {
	m_placement.m_x = x;
	m_placement.m_xw = xw;
	m_placement.m_y = y;
	m_placement.m_yh = yh;
}

Character::Character(PCWSTR img = L"") {
	x = y = 0.0f;
	m_image = img;
}

PCWSTR Character::getImage() {
	return m_image;
}
