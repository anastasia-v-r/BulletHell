#include "game.hpp"
#include <SFML/Graphics.hpp>

Game::Game() {
	auto mode = sf::VideoMode::getDesktopMode();
	mode.height += 1;
	mWindow.create(mode, "Bullet Hell!", sf::Style::None);
}

void Game::runGame() {
	mStateManager.processStack(mWindow);
}

Game::~Game() {

}
