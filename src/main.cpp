// Includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bullet.hpp"
#include "player.hpp"
#include "boss.hpp"
#include <vector>
#include <queue>
#include <map>
#include <iostream>

//************************
// Function Declarations *
//************************

void processInput(sf::RenderWindow& /* window */, float& /* timeModifier */,
				  std::map<std::string, bool>& /*keyMap*/, bool& /* close */);

void updateGame(sf::Time /* Current Time */, sf::Time /* Time since last update */,
				sf::Text& /* hp */, sf::VideoMode /* mode */,
				Player& /* player */,
				sf::RectangleShape& /* enemy */, int& /* enemyHp */,
				std::vector<Bullet>& /*enemyBullets*/, std::vector<Bullet>& /*playerBullets*/,
				const std::map<std::string, bool>& /*keyMap*/, bool& /* close */, float /* timeModifier */);

void renderGame(Player& /* player */, sf::RectangleShape& /* enemy */,
				std::vector<Bullet>& /*enemyBullets*/, std::vector<Bullet>& /*playerBullets*/,
				sf::Text& /* hp */, sf::RenderWindow& /* window */);

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
	Player player(mode);
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
	sf::Time lastUpdate = sf::Time::Zero;
	std::queue<sf::Time> fps;
	float timeModifier = 1.0f;
	// Misc Vars
	bool close = false;
	// Run While the window is open
	while (window.isOpen()) {
		// Process Events
		processInput(window, timeModifier, keyMap, close);
		// Update Game
		updateGame(gameClock.getElapsedTime(), lastUpdate, hp, mode, player, enemy, enemyHp, enemyBullets, playerBullets, keyMap, close, timeModifier);
		lastUpdate = gameClock.getElapsedTime();
		// Draw objects
		renderGame(player, enemy, enemyBullets, playerBullets, hp, window);
		// Calculate Fps
		fps.push(gameClock.getElapsedTime());
		while (fps.front() < (gameClock.getElapsedTime() - (sf::seconds)(1)))
			fps.pop();
		window.setTitle(L"『弾幕』 FPS : " + (std::to_wstring(fps.size() / 1)));
		if (close)
			window.close();
	}
}
//***********************
// Function Definitions *
//***********************

void processInput(sf::RenderWindow& window, float& timeModifier,
	std::map<std::string, bool>& keyMap, bool& close) {
	sf::Event evnt;
	while (window.pollEvent(evnt)) {
		switch (evnt.type)
		{
		case sf::Event::KeyPressed:
			switch (evnt.key.code)
			{
			case sf::Keyboard::Escape:
				close = true;
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
}

void updateGame(sf::Time CurrentTime, sf::Time LastUpdate, 
				sf::Text& hp, sf::VideoMode mode,
				Player& player,
				sf::RectangleShape& enemy, int& enemyHp,
				std::vector<Bullet>& enemyBullets, std::vector<Bullet>& playerBullets,
				const std::map<std::string, bool>& keyMap, bool& close, float timeModifier) {
	sf::Time elapsedTime = (CurrentTime - LastUpdate) / timeModifier;
	static sf::Time bulletTimeBank;
	static sf::Time bossTimeBank;
	static bool goRight = false;
	float fireRate = 1.0f / 5.0f;
	float bossFireRate = 1.0f / 4.0f;
	float enemySpeed = 200.0f;
	// Player movement
	player.move(elapsedTime, keyMap);
	// Player firing
	if (keyMap.at("Space"))
		if (bulletTimeBank.asSeconds() > fireRate) {
			playerBullets.push_back(Bullet(player.obj().getPosition(), 1.0f, true));
			playerBullets.push_back(Bullet(player.obj().getPosition() + sf::Vector2f(player.obj().getSize().x, 0.0f), 1.0f, true));
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
		if (enemy.getGlobalBounds().contains(bullet.getPos()) && bullet.getVal()) {
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
		if (player.obj().getGlobalBounds().contains(bullet.getPos())) {
			close = player.dmg();
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
}

void renderGame(Player& player, sf::RectangleShape& enemy,
	std::vector<Bullet>& enemyBullets, std::vector<Bullet>& playerBullets,
	sf::Text& hp, sf::RenderWindow& window) {
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
}