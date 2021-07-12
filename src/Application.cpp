#include "Game.h"

int main(int argc, char** argv) {

	const char* map;
	if (argc > 1)
		map = argv[1];
	else
		map = "res/templates/glider.txt"; // Default map

	Game game(map);
	game.Start();
	return EXIT_SUCCESS;
}