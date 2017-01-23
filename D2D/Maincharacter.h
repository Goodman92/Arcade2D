#pragma once
#include "Character.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>  
#include <sstream>
#include <iterator>
#include <algorithm>
#include <chrono>

class Maincharacter : public Character {
public:
	Maincharacter(PCWSTR img);
	void animate();
	void resetAnimation(std::string motion);
	void motion(std::string mot);
	bool isWalking;
	bool isJumping;
private:
	double jumptime;
	void switchImage();
	bool isDucking;
	int direction;
	void initializeSpriteFromFile();
	void initializeAnimation();
	std::map<std::string, std::vector<std::string>> movements;
	std::vector<std::string> animationKeys;
	int animationIndex;
	GameTimer m_timer;
	GameTimer animationtimer;
};

Maincharacter::Maincharacter(PCWSTR img = L"") : Character(img), animationIndex(0) {
	jumptime = 2000;
	isDucking = isWalking = isJumping =false;
	initializeSpriteFromFile();
	initializeAnimation();
	switchImage();
}

void Maincharacter::motion(std::string mot) {
	isDucking = mot == "duck" ? true : false;
	isJumping = mot == "jump" ? true : false;
	animationtimer.resetClock();
	auto e = movements.find(mot);
	setDim(stod(e->second[0]), stod(e->second[1]), stod(e->second[2]), stod(e->second[3]));
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

void Maincharacter::resetAnimation(std::string motion) {
	
	if (motion == "duck")
		isDucking = false;
	if (motion == "walk")
		isWalking = false;

	if(!isJumping) {
		animationIndex = 0;
		switchImage();
	}
}

void Maincharacter::animate() {

	if(!isDucking && isWalking && !isJumping) {
		if (animationIndex < animationKeys.size()) {
			switchImage();
			animationIndex++;		
		}
		else {
			animationIndex = 0;
		}
	}
}

// korjaa kunnolliseks
void Maincharacter::switchImage() {
	auto e = movements.find(animationKeys[animationIndex]);
	setDim(stod(e->second[0]), stod(e->second[1]), stod(e->second[2]), stod(e->second[3]));
}