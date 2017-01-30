#include "Game.h"


int main(int argc, char ** argv) {
	Game game("Basic game engine", 700, 700);

	try {
		game.run();
	}
	catch (std::exception e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	return 0;
}