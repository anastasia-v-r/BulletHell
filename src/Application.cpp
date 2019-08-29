#include "Application.h"
#include <stateManager/StateManager.h>

const sf::Time Application::FrameTime = sf::seconds(1.f / 60.f);

Application::Application() {
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	mode.height += 1;
	mWindow.create(mode, "BulletHell", sf::Style::None);
}

void Application::runApp() {
	sf::Clock clock;
	sf::Time lastUpdate = sf::Time::Zero;

	while (mWindow.isOpen()) {
		sf::Time delta = clock.restart();
		lastUpdate += delta;
		while (lastUpdate > FrameTime) {
			lastUpdate -= FrameTime;

			processInput();
			updateGame(FrameTime);

			if (mStateStack.isEmpty()) {
				mWindow.close();
			}
		}
	}
}

void Application::processInput() {
	sf::Event evnt;
	while (mWindow.pollEvent(evnt)) {
		mStateStack
	}
}

void Application::updateGame(sf::Time delta) {

}

void Application::renderGame() {

}
