#include "SplashState.hpp"

SplashState::SplashState() {
	auto screen = sf::VideoMode::getDesktopMode();
	splashImage.setSize(sf::Vector2f(screen.width, screen.height));
	image.loadFromFile("assets/splashScreen/BulletHellSplash.png");
	splashImage.setTexture(&image);
}

void SplashState::HandleInput(sf::RenderWindow& window) {
	sf::Event evnt;
	while (window.pollEvent(evnt)) {
		switch (evnt.type)
		{
		case sf::Event::KeyPressed:
			moveState = true;
			nextState = StateEnum::Game;
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