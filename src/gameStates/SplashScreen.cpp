#include "SplashScreen.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

void SplashScreen::run(sf::RenderWindow& window) {
	sf::Texture splashImage;
	std::cout << std::filesystem::current_path() << std::endl;
	if (splashImage.loadFromFile("resources/BulletHellSplash.png") != true) {
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