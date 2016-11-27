#pragma once

class Debugger {
public:
	Debugger();
	void debugInt(int value);
private:
	WCHAR* buffer;
	Scene m_scene;
};

Debugger::Debugger() {
	buffer = L"Placeholder";
}

void Debugger::debugInt(int value) {
	/*
	_itow_s(value, buffer, sizeof(buffer) / sizeof(WCHAR), 10);
	m_scene.drawText(buffer);
	*/
}