#include "Application.hpp"

Application::Application() {
	auto mode = sf::VideoMode::getDesktopMode();
	mode.height += 1;
	mWindow.create(mode, "BulletHell", sf::Style::Default);
}

void Application::run() {
	sf::RectangleShape box(sf::Vector2f(10, 10));
	while (!exiting) {
		mWindow.clear();
		mWindow.draw(box);
		mWindow.display();
	}
}