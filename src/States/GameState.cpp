#include "GameState.hpp"
#include "Globals.hpp"
#include "Entities/Player.hpp"
#include "Entities/Boss.hpp"
#include "Entities/Bullet.hpp"
#include <iostream>

GameState::GameState() 
	: State(StateID::GAME)
	, player(GlobalData::TRUE_MODE)
	, boss(GlobalData::TRUE_MODE) {
	if (!font.loadFromFile("assets/Global/font/OpenSans-Regular.ttf"))
		std::cout << "Font Failed to load" << std::endl;
	sf::Text hp("HP : ", font, 30);
}

void GameState::update(sf::Time elapsedTime, bool& close) {
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
	boss.move(elapsedTime);
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