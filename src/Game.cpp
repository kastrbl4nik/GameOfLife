#include "Game.h"
#include <fstream>

Game::Game(const char* map) : Engine(100, 60, 8), m_mapWidth(100), m_mapHeight(60)
{
	m_map = new bool[100 * 60];
	memset(m_map, 0, sizeof(bool) * 100 * 60);

	std::wifstream levelData(map);
	ASSERT(levelData);				// Map file wasn't open
	
	std::wstring line;

	for (int y = 0; levelData >> line; y++)
	{
		for (int x = 0; x < line.length(); x++)
		{
			if (line[x] == L'#')
				m_map[x + y * m_mapWidth] = true;
		}
	}
}

Game::~Game()
{
	delete[] m_map;
}

void Game::OnGameStarted() 
{
}

void Game::Update() 
{
	for (int y = 0; y < m_mapHeight; y++)
	{
		for (int x = 0; x < m_mapWidth; x++)
		{
			if (m_map[x + y * m_mapWidth])
				SetSymbol(x, y, { L' ',  COLOR::BG_CYAN });
			else
				SetSymbol(x, y, { L' ',  COLOR::BG_BLACK });
		}
	}
}