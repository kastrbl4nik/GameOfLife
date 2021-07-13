#include "Game.h"
#include <fstream>

int Game::CountNeighbours(int x, int y)
{
	int num =
		m_previousGeneration[(x - 1 >= 0 ? x - 1 : m_mapWidth - 1) + (y - 1 >= 0 ? y - 1 : m_mapHeight - 1) * m_mapWidth] +
		m_previousGeneration[(x - 1 >= 0 ? x - 1 : m_mapWidth - 1) +  y                                     * m_mapWidth] +
		m_previousGeneration[(x - 1 >= 0 ? x - 1 : m_mapWidth - 1) + (y + 1 < m_mapHeight ? y + 1 : 0)      * m_mapWidth] +
		m_previousGeneration[ x                                    + (y - 1 >= 0 ? y - 1 : m_mapHeight - 1) * m_mapWidth] +
		m_previousGeneration[ x                                    + (y + 1 < m_mapHeight ? y + 1 : 0)      * m_mapWidth] +
		m_previousGeneration[(x + 1 < m_mapWidth ? x + 1 : 0)      + (y - 1 >= 0 ? y - 1 : m_mapHeight - 1) * m_mapWidth] +
		m_previousGeneration[(x + 1 < m_mapWidth ? x + 1 : 0)      +  y                                     * m_mapWidth] +
		m_previousGeneration[(x + 1 < m_mapWidth ? x + 1 : 0)      + (y + 1 < m_mapHeight ? y + 1 : 0)      * m_mapWidth];
	return num;
}

Game::Game(const char* map) : Engine(100, 60, 8), m_mapWidth(100), m_mapHeight(60)
{
	m_currentGeneration = new bool[100 * 60];
	m_previousGeneration = new bool[100 * 60];
	memset(m_currentGeneration, 0, sizeof(bool) * 100 * 60);
	memset(m_previousGeneration, 0, sizeof(bool) * 100 * 60);

	std::wifstream levelData(map);
	ASSERT(levelData);				// Map file wasn't open
	
	std::wstring line;

	for (int y = 0; levelData >> line; y++)
	{
		for (int x = 0; x < line.length(); x++)
		{
			if (line[x] == L'#')
			{
				m_currentGeneration[x + y * m_mapWidth] = true;
				m_previousGeneration[x + y * m_mapWidth] = true;
			}
		}
	}
}

Game::~Game()
{
	delete[] m_currentGeneration;
	delete[] m_previousGeneration;
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
			if (m_currentGeneration[x + y * m_mapWidth])
				SetSymbol(x, y, { L' ',  COLOR::BG_CYAN });
			else
				SetSymbol(x, y, { L' ',  COLOR::BG_BLACK });
		}
	}

	if (m_timer >= m_generationLifespan && !m_paused)
	{
		bool* tmp = m_previousGeneration;
		m_previousGeneration = m_currentGeneration;
		m_currentGeneration = tmp;
		for (int y = 0; y < m_mapHeight; y++)
		{
			for (int x = 0; x < m_mapWidth; x++)
			{
				int neighbours = CountNeighbours(x, y);
				if (m_previousGeneration[x + y * m_mapWidth])
					m_currentGeneration[x + y * m_mapWidth] = (neighbours == 2 || neighbours == 3);
				else
					m_currentGeneration[x + y * m_mapWidth] = (neighbours == 3);
			}
		}
		m_timer = 0;
	} 
	else
		m_timer += m_deltaTime;

	if (m_keys[VK_SPACE].pressed)
		m_paused = !m_paused;
}