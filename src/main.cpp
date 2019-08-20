#include "game/game.hpp"

int main() {
	Game game;
	game.run();
	system("pause");
}

/*Notes
Make the statemanager process the game, Game will only instance the statemanager itself.

*/ 