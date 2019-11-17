#pragma once
#include <SFML/Graphics.hpp>
#include "bullet.hpp"
#include <cmath>

class Player : public sf::Drawable
{
public:
	// Cons. & Desc.
	Player(sf::VideoMode mode) 
		: player{ 10.0f }
		, hp{ 3 }
		, speed{ 500.0f }
		, fireRate{ 1.0f / 10.0f } 
		, timeBank{ sf::Time::Zero } {
		player.setPosition(mode.width / 2.0f, mode.height / 2.0f);
		player.setFillColor(sf::Color::Green);
		player.setOrigin(player.getRadius(), player.getRadius());
		bul1.loadFromFile("assets/textures/player_bullet_1.png");
		bul2.loadFromFile("assets/textures/player_bullet_2.png");
	}
	// Processors
	void move(sf::Time /* elapsedTime */, const std::map<std::string, bool>& /* keyMap */);
	void fire(const sf::Time& /* elapsedTime */, std::vector<Bullet>& /* bullets */, const bool& /* fire */);
	bool detectCollide(std::vector<Bullet>& /* bullets */);
	// Getters
	// Draw
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(player, states);
	}
private:
	sf::CircleShape player;
	int hp;
	float speed;
	sf::Time timeBank;
	float fireRate;
	sf::Texture bul1;
	sf::Texture bul2;
};

