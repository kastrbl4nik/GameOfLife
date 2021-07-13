#pragma once
#ifndef GAME_H
#define GAME_H

#define ASSERT(x) if (!(x)) __debugbreak();

#include "Engine.h"


class Game : public Engine {
private:
	bool* m_currentGeneration;
	bool* m_previousGeneration;
	int m_mapWidth;
	int m_mapHeight;
	int CountNeighbours(int x, int y);
	float m_timer = 0.0f;
	float m_generationLifespan = 0.01f;
	bool m_paused = false;
public:
	Game(const char* map);
	~Game();

	void OnGameStarted() override;
	void Update() override;
};


#endif GAME_H // !GAME_H