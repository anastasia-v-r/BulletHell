#include "Application.h"

Application::Application() {
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	mode.height += 1;
	mWindow.create(mode, "BulletHell", sf::Style::None);
}

void Application::runApp() {
	sf::Clock clock;
	sf::Time elapsedTime = sf::Time::Zero;

	while (mWindow.isOpen()) {

	}
}

void Application::proccessInput() {

}

void Application::updateGame() {

}

void Application::renderGame() {

}
