#pragma once
#include "State.hpp"
#include "Entities/Player.hpp"
#include "Entities/Boss.hpp"
#include "Entities/Bullet.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class GameState : public State
{
public:
	GameState();
	void update(sf::Time /* elapsedTime */, bool& /* close */) override;
	void draw(sf::RenderWindow& /* window */) override;
private:
	// Player
	Player player;
	// Enemy
	Boss boss;
	// Enemy Hp
	sf::Font font;
	sf::Text hp;
	// Bullet vectors
	std::vector<Bullet> enemyBullets;
	std::vector<Bullet> playerBullets;
};