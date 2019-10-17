#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bullet.hpp"
#include <vector>
#include <queue>
#include <map>
#include <iostream>

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
	sf::RectangleShape player(sf::Vector2f(20.0f, 20.0f));
	player.setPosition(mode.width / 2.0f, mode.height / 2.0f);
	player.setFillColor(sf::Color::Green);
	int playerHp = 3;
	// Enemy
	sf::RectangleShape enemy(sf::Vector2f(50.0f, 50.0f));
	enemy.setPosition(mode.width / 2.0f, 0.0f);
	int enemyHp = 100;
	// Enemy Hp
	sf::Font font;
	if (!font.loadFromFile("assets/Global/font/OpenSans-Regular.ttf"))
		std::cout << "Font Failed to load" << std::endl;
	sf::Text hp("HP : ", font, 30);
	// Bullet vectors
	std::vector<Bullet> enemyBullets;
	std::vector<Bullet> playerBullets;
	// Setup clocks
	sf::Clock gameClock;
	sf::Clock fixedClock;
	sf::Time bulletTimeBank;
	sf::Time bossTimeBank;
	std::queue<sf::Time> fps;
	float timeModifier = 1.0f;
	// Misc Vars
	bool goRight = false;
	bool close = false;
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
		float fireRate = 1.0f / 5.0f;
		float bossFireRate = 1.0f / 4.0f;
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
				playerBullets.push_back(Bullet(player.getPosition(), 1.0f, true));
				playerBullets.push_back(Bullet(player.getPosition() + sf::Vector2f(player.getSize().x, 0.0f), 1.0f, true));
				bulletTimeBank -= (sf::seconds)(fireRate);
			}
			else
				bulletTimeBank += elapsedTime;
		// Process Bullets
		if (!playerBullets.empty()) {
			for (auto& bullet : playerBullets) {
				bullet.travel(elapsedTime);
			}
		}
		if (!enemyBullets.empty()) {
			for (auto& bullet : enemyBullets) {
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
			enemyBullets.push_back(Bullet(enemy.getPosition() + sf::Vector2f(0.0f, enemy.getSize().y), -1.0f, false));
			enemyBullets.push_back(Bullet(enemy.getPosition() + sf::Vector2f(enemy.getSize().x, enemy.getSize().y), -1.0f, false));
			bossTimeBank -= (sf::seconds)(bossFireRate);
		}
		else
			bossTimeBank += elapsedTime;
		// Boss Collision Detection
		for (auto& bullet : playerBullets) {
			if (enemy.getGlobalBounds().contains(bullet.getPos()) && bullet.getPlr() && bullet.getVal()) {
				bullet.invalidate();
				enemyHp -= 5;
				if (enemyHp < 75 && enemyHp >= 50)
					enemy.setFillColor(sf::Color::Yellow);
				else if (enemyHp < 50 && enemyHp >= 25)
					enemy.setFillColor(sf::Color(255, 98, 0));
				else if (enemyHp < 25 && enemyHp >= 1)
					enemy.setFillColor(sf::Color::Red);
				else if (enemyHp < 1)
					close = true;
			}
		}
		hp.setString("HP : " + std::to_string(enemyHp));
		// Player Collission Detection
		bool wipe = false;
		for (auto& bullet : enemyBullets) {
			if (player.getGlobalBounds().contains(bullet.getPos()) && !bullet.getPlr()) {
				playerHp--;
				if (playerHp == 2)
					player.setFillColor(sf::Color(255, 98, 0));
				else if (playerHp == 1)
					player.setFillColor(sf::Color::Red);
				else
					close = true;
				wipe = true;
				break;
			}
		}
		if (wipe)
			enemyBullets.clear();
		// Clear Bullets
		if (!playerBullets.empty()) {
			for (int i = 0; i < playerBullets.size(); i++) {
				if ((playerBullets[i].getHeight() < 0.1f || playerBullets[i].getHeight() > 1080.0f))
					playerBullets.erase(playerBullets.begin() + i);
			}
		}
		if (!enemyBullets.empty()) {
			for (int i = 0; i < enemyBullets.size(); i++) {
				if ((enemyBullets[i].getHeight() < 0.1f || enemyBullets[i].getHeight() > 1080.0f))
					enemyBullets.erase(enemyBullets.begin() + i);
			}
		}
		// Draw objects
		window.clear();
		window.draw(player);
		window.draw(enemy);
		window.draw(hp);
		if (!playerBullets.empty())
			for (const auto& bullet : playerBullets) {
				window.draw(bullet);
			}
		if (!enemyBullets.empty())
			for (const auto& bullet : enemyBullets) {
				window.draw(bullet);
			}
		window.display();
		// Calculate Fps
		fps.push(gameClock.getElapsedTime());
		while (fps.front() < (gameClock.getElapsedTime() - (sf::seconds)(1)))
			fps.pop();
		window.setTitle(L"『弾幕』 FPS : " + (std::to_wstring(fps.size() / 1)));
		if (close)
			window.close();
	}
}