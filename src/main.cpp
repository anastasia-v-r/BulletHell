#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bullet.hpp"
#include <vector>
#include <map>

int main() {
	std::map<std::string, bool> keyMap = {
		{"Up", false},
		{"Right", false},
		{"Down", false},
		{"Left", false}
	};
	// Create Render Window
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Danmaku", sf::Style::Default);
	window.setKeyRepeatEnabled(false);
	// Test object
	sf::RectangleShape box(sf::Vector2f(50.0f, 50.0f));
	box.setFillColor(sf::Color::Red);
	// Bullet vector
	std::vector<Bullet> bullets;
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
				case sf::Keyboard::Space:
					bullets.push_back(Bullet(box.getPosition()));
					break;
				case sf::Keyboard::W:
					keyMap["Up"] = true;
					break;
				case sf::Keyboard::D:
					keyMap["Right"] = true;
					break;
				case sf::Keyboard::S:
					keyMap["Down"] = true;
					break;
				case sf::Keyboard::A:
					keyMap["Left"] = true;
					break;
				default:
					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (evnt.key.code)
				{
				case sf::Keyboard::W:
					keyMap["Up"] = false;
					break;
				case sf::Keyboard::D:
					keyMap["Right"] = false;
					break;
				case sf::Keyboard::S:
					keyMap["Down"] = false;
					break;
				case sf::Keyboard::A:
					keyMap["Left"] = false;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		// Update Game
		if (keyMap["Up"])
			box.move(0, -.1);
		if (keyMap["Right"])
			box.move(.1, 0);
		if (keyMap["Down"])
			box.move(0, .1);
		if (keyMap["Left"])
			box.move(-.1, 0);
		if (!bullets.empty())
			for (auto& bullet : bullets) {
				bullet.travel();
			}
		// Draw objects
		window.clear();
		window.draw(box);
		if (!bullets.empty())
			for (const auto& bullet : bullets) {
				window.draw(bullet);
			}
		window.display();
	}
}