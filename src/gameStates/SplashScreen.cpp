#include "SplashScreen.hpp"
#include <SFML/Graphics.hpp>

void SplashScreen::run(sf::RenderWindow& window) {
	sf::Texture splashImage;
	if (splashImage.loadFromFile("assets/splashScreen/BulletHellSplash.png") != true) {
		return;
	}
	sf::Sprite splashSprite(splashImage);
	window.clear();
	window.draw(splashSprite);
	window.display();
	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type)
			{
			case sf::Event::KeyPressed:
				return;
			}
		}
	}
}