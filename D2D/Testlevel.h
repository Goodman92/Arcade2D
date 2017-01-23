#pragma once
#include "Baselevel.h"
#include "Maincharacter.h"
#include <vector>

class Testlevel : public Baselevel {
public:
	Testlevel();
	void run();
	void handleKeyStroke(KEYSTROKES key);
	void handleMultiKeyStrokes(std::vector<KEYSTROKES> keys);
	void handleRelease(int key);

private:
	void checkKeys(KEYSTROKES key);
	Scene m_scene;
	Map m_map;
	GameTimer m_timer;
	Maincharacter m_maincharacter;
	RECT rc;
	float time, time2;
};

Testlevel::Testlevel() : Baselevel(), m_map(0.0f, 0.0f, L"bg_shroom.png"), m_maincharacter(L"p1_spritesheet.png") {
	time = 0.0f;
	time2 = 0.0f;
	m_scene.fionalisti(rc);
	m_map.setRect(rc);
	m_maincharacter.m_placement.y = 0;
	m_scene.setGameComponents(&m_maincharacter);
	m_scene.setGameComponents(&m_map);
	m_scene.setMapComponent(&m_map);
}

void Testlevel::run() {
	m_scene.update();
	float horizontalMovementInTiles = m_map.m_placement.m_x / 70.0;
	float verticalMovementInTiles = (m_maincharacter.m_placement.y + 97) / 70.0;
	std::wstring ws;

	float tileSurface = 70 * ((int)ceil(verticalMovementInTiles));
	float characterFloor = m_maincharacter.m_placement.y + 97;
	int hasTile = m_map.hasTile((int)ceil(verticalMovementInTiles), (int)round(horizontalMovementInTiles));

	if (hasTile == 1 && characterFloor < tileSurface && !m_maincharacter.isJumping) {
		time += 0.1f;
		float distance = 0.5 * 9.81 * time*time; // d = 0.5 * g * t^2
		float sum = m_maincharacter.m_placement.y + distance;

		if (characterFloor + distance > tileSurface) {
			m_maincharacter.m_placement.y += tileSurface - characterFloor;
		} 
		else {
			m_maincharacter.m_placement.y += distance;
		}
	}
	else if (hasTile == 0 && !m_maincharacter.isJumping) {
		time += 0.1f;
		float distance = 0.5 * 9.81 * time*time; // d = 0.5 * g * t^2
		float sum = m_maincharacter.m_placement.y + distance;
		m_maincharacter.m_placement.y += distance;
	}
	else {
		time = 0.0;
	}

	if (m_maincharacter.isJumping) {
		time2 += 0.1f;
		float height = 12 * time2 - 0.5 * 9.81 * time2 * time2; // y = v0t - 0.5gt^2
		m_maincharacter.m_placement.y -= height;
		float horizontalMovementInTiles = m_map.m_placement.m_x / 70;
		float verticalMovementInTiles = (m_maincharacter.m_placement.y + 97) / 70;
		int hasTile = m_map.hasTile((int)floor(verticalMovementInTiles), (int)ceil(horizontalMovementInTiles));
		
		if (hasTile == 1) {
			m_maincharacter.isJumping = false;
			m_maincharacter.m_placement.y = (int)floor(verticalMovementInTiles) * 70 - 97;
		}
		
	}
	else {
		time2 = 0.0;
	}


	const WCHAR* jq = ws.c_str();
	OutputDebugString(jq);

	/*
	m_scene.startDrawing();
	m_scene.drawBackground(m_map.getBgImage(), m_map.getHorizontalPosition(), m_map.getVerticalPosition());
	m_maincharacter.animate();
	m_map.scroll();
	m_scene.drawImage(m_maincharacter.getImg(), m_maincharacter.x, m_maincharacter.y, m_maincharacter.getX(), m_maincharacter.getY(), m_maincharacter.getXW(), m_maincharacter.getYH());
	m_map.initializeTiles();
	auto tiles = m_map.getTilePositions();
	for (auto o : tiles) {
		m_scene.drawImage(L"tiles_spritesheet.png", o.at(0), o.at(1), 576, 864, o.at(2), 70);
	}
	m_scene.endDrawing();
	*/
}

void Testlevel::handleMultiKeyStrokes(std::vector<KEYSTROKES> keys) {
	for (auto k : keys) {
		checkKeys(k);
	}
}

void Testlevel::handleKeyStroke(KEYSTROKES key) {
	checkKeys(key);
}

void Testlevel::checkKeys(KEYSTROKES key) {
	switch (key) {
		case KEYSTROKES::left:
			m_map.setHorizontalPosition(-4.5f);
			m_maincharacter.isWalking = m_map.isScrolling = true;
			break;

		case KEYSTROKES::right:
			m_map.setHorizontalPosition(4.5f);
			m_maincharacter.isWalking = m_map.isScrolling = true;
			break;

		case KEYSTROKES::duck:
			m_maincharacter.motion("duck");
			break;

		case KEYSTROKES::jump:
			m_maincharacter.motion("jump");
			break;
	}
}

void Testlevel::handleRelease(int key) {
	switch (key) {
	case KEYSTROKES::left:
	case KEYSTROKES::right:
		m_maincharacter.resetAnimation("walk");
		m_maincharacter.isWalking = m_map.isScrolling = false;
		break;

	case KEYSTROKES::duck:
		m_maincharacter.resetAnimation("duck");
		break;
	case KEYSTROKES::jump:
		m_maincharacter.resetAnimation("jump");
		break;
	}
}

/*
void Testlevel::debug() {
	WCHAR buf[] = L"textiiiiiiiiiiiIIIIIII";

	std::wstring ws;

	_itow_s(m_maincharacter.x, buf, sizeof(buf) / sizeof(WCHAR), 10);
	ws.append(buf);
	ws.append(L" | ");
	_itow_s(m_maincharacter.y, buf, sizeof(buf) / sizeof(WCHAR), 10);
	ws.append(buf);
	ws.append(L" | ");

	_itow_s(m_maincharacter.getX(), buf, sizeof(buf) / sizeof(WCHAR), 10);
	ws.append(buf);
	ws.append(L" | ");
	_itow_s(m_maincharacter.getY(), buf, sizeof(buf) / sizeof(WCHAR), 10);
	ws.append(buf);
	ws.append(L" | ");
	_itow_s(m_maincharacter.getXW(), buf, sizeof(buf) / sizeof(WCHAR), 10);
	ws.append(buf);
	ws.append(L" | ");
	_itow_s(m_maincharacter.getYH(), buf, sizeof(buf) / sizeof(WCHAR), 10);
	ws.append(buf);
	ws.append(L" | ");

	const WCHAR* jq = ws.c_str();
	m_scene.drawText(jq);
}
*/