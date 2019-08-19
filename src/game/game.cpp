#include "game.hpp"
#include <SFML/Graphics.hpp>

Game::Game() {
	auto mode = sf::VideoMode::getDesktopMode();
	mode.height += 1;
	mWindow.create(mode, "Bullet Hell!", sf::Style::None);
}

void Game::run() {
	while (mWindow.isOpen()) {
		processEvents();
		gameLogic();
		draw();
	}
}

void Game::processEvents() {
	sf::Event mEvent;
	while (mWindow.pollEvent(mEvent)) {

	}
}

void Game::gameLogic() {

}

void Game::draw() {
	mWindow.clear();
	mWindow.draw(box);
	mWindow.display();
}

Game::~Game() {

}
