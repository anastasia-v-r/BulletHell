#include "SFML/Graphics.hpp"
#include "MenuScreen.h"

void MenuScreen::run(sf::RenderWindow & window) {
	sf::RectangleShape rect(sf::Vector2f(400, 200));
	rect.setPosition(1000, 500);
	window.clear();
	window.draw(rect);
	window.display();
	sf::Event evnt;
	while (true) {
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::KeyPressed) {
				rect.setFillColor(sf::Color::Blue);
				window.clear();
				window.draw(rect);
				window.display();
			} else if (evnt.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
				if (rect.getGlobalBounds().contains(mousePosF)) {
					rect.setFillColor(sf::Color::Red);
					window.clear();
					window.draw(rect);
					window.display();
				}
			}
		}
	}
}