// Includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "globals.hpp"
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

void ResizeView(const sf::RenderWindow& /* window */, sf::View& /* view */);

void processInput(sf::RenderWindow& /* window */, float& /* timeModifier */,
	bool& /* close */, sf::View& /* camera */);

void updateGame(sf::Time /* Current Time */, sf::Time /* Time since last update */,
	sf::Text& /* hp */, sf::VideoMode /* mode */,
	Player& /* player */, Boss& /* boss */,
	std::vector<Bullet>& /*enemyBullets*/, std::vector<Bullet>& /*playerBullets*/,
	bool& /* close */, float /* timeModifier */);

void renderGame(Player& /* player */, Boss& /* enemy */,
	std::vector<Bullet>& /*enemyBullets*/, std::vector<Bullet>& /*playerBullets*/,
	sf::Text& /* hp */, sf::RenderWindow& /* window */);

int main() {
	// Create Render Window
	auto realmode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(realmode, L"弾幕", sf::Style::Default);
	// Setup View
	sf::View view(sf::Vector2f(TRUE_WIDTH / 2.0f, TRUE_HEIGHT / 2.0f), sf::Vector2f(TRUE_WIDTH, TRUE_HEIGHT));
	ResizeView(window, view);
	window.setView(view);
	window.setPosition(sf::Vector2i(1, 0));
	window.setKeyRepeatEnabled(false);
	// Player
	Player player(TRUE_MODE);
	// Enemy
	Boss boss(TRUE_MODE);
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
		processInput(window, timeModifier, close, view);
		// Update Game
		updateGame(gameClock.getElapsedTime(), lastUpdate, hp, TRUE_MODE, player, boss, enemyBullets, playerBullets, close, timeModifier);
		lastUpdate = gameClock.getElapsedTime();
		// Draw objects
		renderGame(player, boss, enemyBullets, playerBullets, hp, window);
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

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
	if ((float)window.getSize().x / (float)window.getSize().y != TRUE_WIDTH / TRUE_WIDTH) {
		std::cout << "NOT 16:9" << std::endl;
		float aspectRatio = (float)window.getSize().x / (float)window.getSize().y;
		if (aspectRatio > TRUE_WIDTH / TRUE_HEIGHT) { // Side bars
			view.setViewport(sf::FloatRect((1.0f - (TRUE_RATIO / aspectRatio)) / 2.0f, 0.0f, TRUE_RATIO / aspectRatio, 1.0f));
		}
		else { // Bars on top and under
			view.setViewport(sf::FloatRect(0.0f, (1.0f - (aspectRatio / TRUE_RATIO)) / 2.0f, 1.0f, aspectRatio / TRUE_RATIO));
		}
	}
	else {
		view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	}
}

void processInput(sf::RenderWindow& window, float& timeModifier,
	bool& close, sf::View& view) {
	sf::Event evnt;
	while (window.pollEvent(evnt)) {
		switch (evnt.type)
		{
		case sf::Event::Resized:
			ResizeView(window, view);
			window.setView(view);
			break;
		case sf::Event::KeyPressed:
			switch (evnt.key.code)
			{
			case sf::Keyboard::Escape:
				close = true;
				break;
			case sf::Keyboard::LShift:
				timeModifier = 5.0f;
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
		case sf::Event::MouseButtonPressed: {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
			mousePosF = window.mapPixelToCoords(mousePos, view);
		}
			break;
		default:
			break;
		}
	}
}

void updateGame(sf::Time CurrentTime, sf::Time LastUpdate,
	sf::Text& hp, sf::VideoMode mode,
	Player& player, Boss& boss,
	std::vector<Bullet>& enemyBullets, std::vector<Bullet>& playerBullets,
	bool& close, float timeModifier) {
	sf::Time elapsedTime = (CurrentTime - LastUpdate) / timeModifier;

	// Process Bullets
	if (!playerBullets.empty()) {
		for (auto& bullet : playerBullets) {
			bullet.travel(elapsedTime, boss.getPos());
		}
	}
	if (!enemyBullets.empty()) {
		for (auto& bullet : enemyBullets) {
			bullet.travel(elapsedTime, boss.getPos());
		}
	}

	// Process player
	player.move(elapsedTime);
	player.fire(elapsedTime, playerBullets);
	if (player.detectCollide(enemyBullets))
		close = true;

	// Process Boss
	boss.move(elapsedTime, mode);
	boss.fire(elapsedTime, enemyBullets);
	if (boss.detectCollide(playerBullets))
		close = true;
	hp.setString("HP : " + std::to_string(boss.getHp()));

	// Clear Bullets
	if (!playerBullets.empty()) {
		for (int i = 0; i < playerBullets.size(); i++) {
			if ((playerBullets[i].getHeight() < 0.1f || playerBullets[i].getHeight() > 1080.0f) || !playerBullets[i].getVal())
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

void renderGame(Player& player, Boss& boss,
	std::vector<Bullet>& enemyBullets, std::vector<Bullet>& playerBullets,
	sf::Text& hp, sf::RenderWindow& window) {
	window.clear();
	window.draw(player);
	window.draw(boss);
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