#include "SFML/Graphics.hpp"
#include "MenuScreen.h"

void MenuScreen::run(sf::RenderWindow & window) {
	sf::RectangleShape rect(sf::Vector2f(1920, 1080));
	window.clear();
	window.draw(rect);
	window.display();
	sf::Event evnt;
	while (true) {
		while (window.pollEvent(evnt)) {
			switch (evnt.type)
			{
			case sf::Event::KeyPressed:
			case sf::Event::MouseButtonPressed:
				return;
			}
		}
	}
}