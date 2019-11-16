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
	GameState(std::queue<std::pair<StateChange, StateID>>& /* pendingChanges */);
	void input(sf::Event /* evnt */, bool& /* close */, sf::RenderWindow& /* window */, sf::View& /* view */) override;
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