#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bullet.hpp"
#include <vector>
#include <queue>
#include <map>

int main() {
	std::map<std::string, bool> keyMap = {
		{"Up", false},
		{"Right", false},
		{"Down", false},
		{"Left", false},
		{"Space", false }
	};
	// Create Render Window
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), L"弾幕", sf::Style::Default);
	window.setKeyRepeatEnabled(false);
	// Test object
	sf::RectangleShape box(sf::Vector2f(50.0f, 50.0f));
	box.setFillColor(sf::Color::Red);
	// Bullet vector
	std::vector<Bullet> bullets;
	// Setup clocks
	sf::Clock gameClock;
	sf::Clock fixedClock;
	sf::Time bulletTimeBank;
	std::queue<sf::Time> fps;
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
					keyMap["Space"] = true;
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
				case sf::Keyboard::Space:
					keyMap["Space"] = false;
					break;
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
		float boxSpeed = 500.0f;
		float fireRate = 0.1f;
		auto elapsedTime = fixedClock.restart();
		if (keyMap["Up"])
			box.move(0, -boxSpeed * elapsedTime.asSeconds());
		if (keyMap["Right"])
			box.move(boxSpeed * elapsedTime.asSeconds(), 0);
		if (keyMap["Down"])
			box.move(0, boxSpeed * elapsedTime.asSeconds());
		if (keyMap["Left"])
			box.move(-boxSpeed * elapsedTime.asSeconds(), 0);
		if (keyMap["Space"])
			if (bulletTimeBank.asSeconds() > fireRate) {
				bullets.push_back(Bullet(box.getPosition()));
				bulletTimeBank -= (sf::seconds)(fireRate);
			}
			else
				bulletTimeBank += elapsedTime;
		if (!bullets.empty())
			for (auto& bullet : bullets) {
				bullet.travel(elapsedTime);
			}
		// Draw objects
		window.clear();
		window.draw(box);
		if (!bullets.empty())
			for (const auto& bullet : bullets) {
				window.draw(bullet);
			}
		window.display();
		// Calculate Fps
		fps.push(gameClock.getElapsedTime());
		while (fps.front() < (gameClock.getElapsedTime() - (sf::seconds)(1)))
			fps.pop();
		window.setTitle(L"『弾幕』 FPS : " + (std::to_wstring(fps.size() / 1)));
	}
}