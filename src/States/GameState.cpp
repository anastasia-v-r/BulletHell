#include "GameState.hpp"
#include "Globals.hpp"
#include "ResourceManager.hpp"
#include "Entities/Player.hpp"
#include "Entities/Boss.hpp"
#include "Entities/Bullet.hpp"
#include <iostream>

GameState::GameState(std::queue<std::pair<StateChange, StateID>>& pendingChanges)
	: State(StateID::GAME, pendingChanges)
	, player(GlobalData::TRUE_MODE)
	, boss(GlobalData::TRUE_MODE)
	, timeModifier{ 1.0f } 
	, keyMap {
		{"Up", false},
		{"Right", false},
		{"Down", false},
		{"Left", false},
		{"Space", false }
	  } {
	ResourceManager::instance().loadState({
		{"PlayerBullet1", "assets/textures/player_bullet_1.png"},
		{"PlayerBullet2", "assets/textures/player_bullet_2.png"},
		{"BossBullet1"  , "assets/textures/boss_bullet_1.png"  },
		{"BossBullet2"  , "assets/textures/boss_bullet_2.png"  }
	});
	hp = sf::Text("HP : ", ResourceManager::instance().getFont(), 30);
}

void GameState::input(sf::Event evnt, bool& close, sf::RenderWindow& window, sf::View& view) {
	switch (evnt.type)
	{
	case sf::Event::KeyPressed:
		switch (evnt.key.code)
		{
		case sf::Keyboard::Escape:
			pendingChanges.push({ StateChange::REMOVE, StateID::MENU });
			break;
		case sf::Keyboard::BackSpace:
			timeModifier = 0.0f;
			break;
		case sf::Keyboard::LShift:
			timeModifier = 5.0f;
			break;
		case sf::Keyboard::Space:
			this->keyMap["Space"] = true;
			break;
		case sf::Keyboard::W:
			this->keyMap["Up"] = true;
			break;
		case sf::Keyboard::D:
			this->keyMap["Right"] = true;
			break;
		case sf::Keyboard::S:
			this->keyMap["Down"] = true;
			break;
		case sf::Keyboard::A:
			this->keyMap["Left"] = true;
			break;
		default:
			break;
		}
		break;
	case sf::Event::KeyReleased:
		switch (evnt.key.code)
		{
		case sf::Keyboard::LShift:
		case sf::Keyboard::BackSpace:
			timeModifier = 1.0f;
			break;
		case sf::Keyboard::Space:
			this->keyMap["Space"] = false;
			break;
		case sf::Keyboard::W:
			this->keyMap["Up"] = false;
			break;
		case sf::Keyboard::D:
			this->keyMap["Right"] = false;
			break;
		case sf::Keyboard::S:
			this->keyMap["Down"] = false;
			break;
		case sf::Keyboard::A:
			this->keyMap["Left"] = false;
			break;
		default:
			break;
		}
		break;
	case sf::Event::MouseButtonPressed: {
		sf::Vector2f mousePosF = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
		}
	}
}

void GameState::update(sf::Time elapsedTime, bool& close) {
	if (timeModifier != 0.0f)
		elapsedTime /= timeModifier;
	else
		elapsedTime = sf::Time::Zero;
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
	player.move(elapsedTime, this->keyMap);
	player.fire(elapsedTime, playerBullets, this->keyMap.at("Space"));
	if (player.detectCollide(enemyBullets))
		pendingChanges.push({ StateChange::REMOVE, StateID::MENU });

	// Process Boss
	boss.move(elapsedTime);
	boss.fire(elapsedTime, enemyBullets);
	if (boss.detectCollide(playerBullets))
		pendingChanges.push({StateChange::REMOVE, StateID::MENU});
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

void GameState::draw(sf::RenderWindow& window) {
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