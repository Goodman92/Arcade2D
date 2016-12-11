#pragma once

//leakit
class GameComponent {
public:
	virtual ComponentPlacement getDimensions() = 0;
	virtual PCWSTR getImage() = 0;
	virtual void animate() = 0;
};