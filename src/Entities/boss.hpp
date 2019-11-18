#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.hpp"
#include "Globals.hpp"
#include <cmath>

class Boss : public sf::Drawable
{
public:
	Boss(sf::VideoMode mode)
		: boss{ 50.0f }
		, iHp{ 500 }
		, hp{ iHp }
		, speed{ 200.0f } 
		, goRight{ true } 
		, fireRate{ 1.0f / 4.0f } 
		, timeBank{ sf::Time::Zero } {
		bul1.loadFromFile("assets/textures/boss_bullet_1.png");
		bul2.loadFromFile("assets/textures/boss_bullet_2.png");
		boss.setPosition(mode.width / 2.0f, 0.0f);
		boss.setOrigin(boss.getRadius(), boss.getRadius());
	}
	// Processors
	void move(const sf::Time& /* elapsedTime */);
	void fire(const sf::Time& /* elapsedTime */, std::vector<Bullet>& /* bullets */);
	bool detectCollide(std::vector<Bullet>& /* bullets */);
	// Getters
	inline int getHp() const { return hp; }
	inline sf::Vector2f getPos() const { return boss.getPosition(); }
	// Draw
	inline virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const { window.draw(boss, states); }
private:
	sf::CircleShape boss;
	int iHp;
	int hp;
	float speed;
	bool goRight;
	sf::Time timeBank;
	float fireRate;
	sf::Texture bul1;
	sf::Texture bul2;
};