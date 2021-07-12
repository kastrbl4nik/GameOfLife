#pragma once
#ifndef GAME_H
#define GAME_H

#define ASSERT(x) if (!(x)) __debugbreak();

#include "Engine.h"


class Game : public Engine {
private:
	bool* m_map;
	int m_mapWidth;
	int m_mapHeight;
public:
	Game(const char* map);
	~Game();

	void OnGameStarted() override;
	void Update() override;
};


#endif GAME_H // !GAME_H