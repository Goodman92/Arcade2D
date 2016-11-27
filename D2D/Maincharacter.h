#pragma once
#include "Character.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>  
#include <sstream>
#include <iterator>
#include <algorithm>

class Maincharacter : public Character {
public:
	Maincharacter(PCWSTR img);
	void animate();
	void resetAnimation();

	void motion(std::string mot);
	void stopMotion();
	bool isWalking;
private:
	void switchImage();
	bool isDucking;
	bool isJumping;
	int direction;
	void initializeSpriteFromFile();
	void initializeAnimation();
	std::map<std::string, std::vector<std::string>> movements;
	std::vector<std::string> animationKeys;
	int animationIndex;
	GameTimer m_timer;
};

Maincharacter::Maincharacter(PCWSTR img = L"") : Character(img), isDucking(false), isWalking(false), animationIndex(0) {
	initializeSpriteFromFile();
	initializeAnimation();
	switchImage();
}

void Maincharacter::motion(std::string mot) {
	isDucking = mot == "duck" ? true : false;
	auto e = movements.find(mot);
	setDim(stod(e->second[0]), stod(e->second[1]), stod(e->second[2]), stod(e->second[3]));
}

void Maincharacter::stopMotion() {
	isDucking = isJumping = false;
	animationIndex = 0;
	switchImage();
}

void Maincharacter::initializeSpriteFromFile() {
	std::ifstream file("p1_spritesheet.txt");
	std::string line = "";
	if (file.is_open()) {
		while (getline(file, line)) {
			line.erase(remove(line.begin(), line.end(), '='), line.end());
			std::string key = line.substr(0, line.find(" "));
			line = line.substr(line.find_first_of(" ") + 1);
			std::istringstream iss(line);
			std::vector<std::string> col;
			copy(std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				back_inserter(col));
			movements.insert(make_pair(key, col));
		}
	}
}

void Maincharacter::initializeAnimation() {
	for (auto e : movements) {
		auto j = e.first.find("walk");
		if (j == 0) {
			animationKeys.push_back(e.first);
		}
	}
}

void Maincharacter::resetAnimation() {
	isWalking = isDucking = isJumping = false;
	animationIndex = 0;
	switchImage();
}

void Maincharacter::animate() {
	if(!isDucking && isWalking) {
		if (m_timer.delta() >= m_timer.getClockRate()) {
			if (animationIndex < animationKeys.size()) {
				switchImage();
				animationIndex++;
			}
			else {
				animationIndex = 0;
			}
			m_timer.resetClock();
		}
		m_timer.clockTick();
	}
}

// korjaa kunnolliseks
void Maincharacter::switchImage() {
	auto e = movements.find(animationKeys[animationIndex]);
	setDim(stod(e->second[0]), stod(e->second[1]), stod(e->second[2]), stod(e->second[3]));
}