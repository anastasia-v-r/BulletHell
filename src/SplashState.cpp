#include "SplashState.hpp"
#include <filesystem>
#include <iostream>

SplashState::SplashState() {
	auto screen = sf::VideoMode::getDesktopMode();
	splashImage.setSize(sf::Vector2f(screen.width, screen.height));
	std::cout << std::experimental::filesystem::current_path().string() << std::endl;
	image.loadFromFile("assets/splashScreen/BulletHellSplash.png");
	splashImage.setTexture(&image);
}

void SplashState::HandleInput(sf::RenderWindow& window) {
	sf::Event evnt;
	while (window.pollEvent(evnt)) {
		switch (evnt.type)
		{
		case sf::Event::KeyPressed:
			window.close();
		}
	}
}

void SplashState::UpdateGame(sf::RenderWindow& window) {

}

void SplashState::DrawElements(sf::RenderWindow& window) {
	window.clear();
	window.draw(splashImage);
	window.display();
}