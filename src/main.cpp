#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <conio.h>

int main() {
	sf::RenderWindow window;
	window.create(sf::VideoMode::getDesktopMode(), "Danmaku", sf::Style::Default);
	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::KeyPressed) {
				window.close();
			}
		}
		window.clear();
		window.display();
	}
}