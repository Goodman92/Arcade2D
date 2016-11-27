#pragma once
#include "Scene.h"
#include "Map.h"
#include "Debugger.h"

class Baselevel {

public:
	virtual void run() = 0;
	virtual void handleKeyStroke(KEYSTROKES key) = 0;
	virtual void handleMultiKeyStrokes(std::vector<KEYSTROKES> keys) = 0;
	virtual void handleRelease(int key) = 0;
};
