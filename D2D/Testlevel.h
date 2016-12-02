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
	void debug();

private:
	void checkKeys(KEYSTROKES key);
	Scene m_scene;
	Map m_map;
	Maincharacter m_maincharacter;
	std::vector<Character*> m_character;
	Debugger m_debug;
	RECT rc;
	int d;
};

Testlevel::Testlevel() : Baselevel(), m_map(0.0f, 0.0f, L"bg_shroom.png"), m_maincharacter(L"p1_spritesheet.png") {
	m_scene.fionalisti(rc);
	m_map.setRect(rc);
	m_maincharacter.y = 490 - 70 * 3 - 72;
}
// CACHEE BITMAPIT!!!!!!!!!!!!
void Testlevel::run() {
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
		m_map.setHorizontalPosition(-6.5f);
		m_maincharacter.isWalking = true;
		break;

	case KEYSTROKES::right:
		m_map.setHorizontalPosition(6.5f);
		m_maincharacter.isWalking = true;
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
		m_maincharacter.resetAnimation();
		m_map.isScrolling = false;
		break;

	case KEYSTROKES::duck:
	case KEYSTROKES::jump:
		m_maincharacter.stopMotion();
		break;
	}
}

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