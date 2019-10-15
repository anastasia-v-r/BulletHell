#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main() {
	// Create Render Window
	sf::RenderWindow window;
	window.create(sf::VideoMode::getDesktopMode(), "Danmaku", sf::Style::Default);
	// Test object
	sf::RectangleShape box(sf::Vector2f(50.0f, 50.0f));
	box.setFillColor(sf::Color::Red);
	// Run While the window is open
	while (window.isOpen()) {
		// Process Events
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type)
			{
			case sf::Event::KeyPressed:
				switch (evnt.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::W:
					box.move(0.0f, -10.0f);
					break;
				case sf::Keyboard::A:
					box.move(-10.0f, 0.0f);
					break;
				case sf::Keyboard::S:
					box.move(0.0f, 10.0f);
					break;
				case sf::Keyboard::D:
					box.move(10.0f, 0.0f);
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		// Draw objects
		window.clear();
		window.draw(box);
		window.display();
	}
}