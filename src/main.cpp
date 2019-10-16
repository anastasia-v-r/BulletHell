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
	auto mode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(mode, L"弾幕", sf::Style::Default);
	window.setKeyRepeatEnabled(false);
	// Player
	sf::RectangleShape player(sf::Vector2f(10.0f, 10.0f));
	player.setPosition(mode.width / 2.0f, mode.height / 2.0f);
	player.setFillColor(sf::Color::Red);
	// Enemy
	sf::RectangleShape enemy(sf::Vector2f(50.0f, 50.0f));
	enemy.setPosition(mode.width / 2.0f, 0.0f);
	// Bullet vector
	std::vector<Bullet> bullets;
	// Setup clocks
	sf::Clock gameClock;
	sf::Clock fixedClock;
	sf::Time bulletTimeBank;
	sf::Time bossTimeBank;
	std::queue<sf::Time> fps;
	float timeModifier = 1.0f;
	// Misc Vars
	bool goRight = false;
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
				case sf::Keyboard::LShift:
					timeModifier = 2.0f;
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
				case sf::Keyboard::LShift:
					timeModifier = 1.0f;
					break;
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
		float fireRate = 0.02f;
		float bossFireRate = 0.25f;
		float enemySpeed = 200.0f;
		auto elapsedTime = fixedClock.restart() / timeModifier;
		// Player movement
		if (keyMap["Up"])
			player.move(0, -boxSpeed * elapsedTime.asSeconds());
		if (keyMap["Right"])
			player.move(boxSpeed * elapsedTime.asSeconds(), 0);
		if (keyMap["Down"])
			player.move(0, boxSpeed * elapsedTime.asSeconds());
		if (keyMap["Left"])
			player.move(-boxSpeed * elapsedTime.asSeconds(), 0);
		// Player firing
		if (keyMap["Space"])
			if (bulletTimeBank.asSeconds() > fireRate) {
				bullets.push_back(Bullet(player.getPosition(), 1.0f));
				bullets.push_back(Bullet(player.getPosition() + sf::Vector2f(player.getSize().x, 0.0f), 1.0f));
				bulletTimeBank -= (sf::seconds)(fireRate);
			}
			else
				bulletTimeBank += elapsedTime;
		// Process Bullets
		if (!bullets.empty()) {
			for (int i = 0; i < bullets.size(); i++) {
				if (bullets[i].getHeight() < 0.1f || bullets[i].getHeight() > 1080.0f)
					bullets.erase(bullets.begin() + i);
			}
			bullets.shrink_to_fit();
			for (auto& bullet : bullets) {
				bullet.travel(elapsedTime);
			}
		}
		// Enemy movement
		if (enemy.getPosition().x > ((mode.width / 3) * 2))
			goRight = false;
		else if (enemy.getPosition().x < ((mode.width / 3)))
			goRight = true;
		if (goRight)
			enemy.move(enemySpeed * elapsedTime.asSeconds(), 0.0f);
		else
			enemy.move(-enemySpeed * elapsedTime.asSeconds(), 0.0f);
		// Boss firing
		if (bossTimeBank.asSeconds() > bossFireRate) {
			for (int i = 0; i < 50; i += 10) {
				bullets.push_back(Bullet(enemy.getPosition() + sf::Vector2f(i, 0.0f), -1.0f));
			}
			bossTimeBank -= (sf::seconds)(bossFireRate);
		}
		else
			bossTimeBank += elapsedTime;
		// Draw objects
		window.clear();
		window.draw(player);
		window.draw(enemy);
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