#pragma once

#include <chrono>

typedef std::chrono::time_point<std::chrono::system_clock> timePoint;
class GameTimer {

public:
	GameTimer();
	~GameTimer();

	void clockTick();
	double delta();
	inline void resetClock();
	inline double getClockRate();

	double getDifferenceInMS() {
		auto k = std::chrono::duration_cast<std::chrono::milliseconds>(tick - start).count();
		return k;
	}
	timePoint start;
	timePoint tick;
private:
	timePoint step;
	double clockRate;
};

GameTimer::GameTimer() {
	start = std::chrono::system_clock::now();
	step = tick = start;
	clockRate = 1.0 / 60;
}

GameTimer::~GameTimer() { }

double GameTimer::getClockRate() {
	return clockRate;
}

void GameTimer::clockTick() {
	tick = std::chrono::system_clock::now();
}

double GameTimer::delta() {
	std::chrono::duration<double> ticker = tick - start;
	return ticker.count();
}

void GameTimer::resetClock() {
	clockTick();
	start = tick;
}