#pragma once
#include <SFML/Graphics.hpp>
#include "bullet.hpp"
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
		boss.setPosition(mode.width / 2.0f, 0.0f);
		boss.setOrigin(boss.getRadius(), boss.getRadius());
	}
	// Processors
	void move(const sf::Time& elapsedTime, const sf::VideoMode& mode) {
		// Keep in place
		if (boss.getPosition().x > ((mode.width / 3) * 2))
			goRight = false;
		else if (boss.getPosition().x < ((mode.width / 3)))
			goRight = true;
		// Move
		if (goRight)
			boss.move(speed * elapsedTime.asSeconds(), 0);
		else
			boss.move(-speed * elapsedTime.asSeconds(), 0);
	}
	void fire(const sf::Time& elapsedTime, std::vector<Bullet>& bullets) {
		if (timeBank.asSeconds() > fireRate) {
			float speed = 500.0f;
			float size = 20.0f;
			float angVel;
			float dmg = 1;
			if (goRight)
				angVel = -50.0f;
			else
				angVel = 50.0f;
			bullets.push_back(Bullet(boss.getPosition() + sf::Vector2f(boss.getRadius(), boss.getRadius()), 135.0f, false, speed, angVel, dmg, size));
			bullets.push_back(Bullet(boss.getPosition() + sf::Vector2f(boss.getRadius() / 2, boss.getRadius()), 157.5f, false, speed, angVel, dmg, size));
			bullets.push_back(Bullet(boss.getPosition() + sf::Vector2f(0.0f, boss.getRadius()), 180.0f, false, speed, angVel, dmg, size));
			bullets.push_back(Bullet(boss.getPosition() + sf::Vector2f(-boss.getRadius() / 2, boss.getRadius()), 202.5f, false, speed, angVel, dmg, size));
			bullets.push_back(Bullet(boss.getPosition() + sf::Vector2f(-boss.getRadius(), boss.getRadius()), 225.0f, false, speed, angVel, dmg, size));
			timeBank -= (sf::seconds)(fireRate);
		} else {
			timeBank += elapsedTime;
		}
	}
	bool detectCollide(std::vector<Bullet>& bullets) {
		auto [x2, y2] = boss.getPosition();
		float bRad = boss.getRadius();
		for (auto& bullet : bullets) {
			auto [x1, y1] = bullet.getPos();
			if ( bullet.getVal() && std::sqrt(std::pow(y2 - y1, 2) + std::pow(x2 - x1, 2)) < (bRad + bullet.getRadius()) ) {
				bullet.invalidate();
				hp -= bullet.getDmg();
				if (hp < (iHp * 0.75f) && hp >= (iHp * 0.50f)) {
					boss.setFillColor(sf::Color::Yellow);
				} else if (hp < (iHp * 0.50f) && hp >= (iHp * 0.25f)) {
					boss.setFillColor(sf::Color(255, 98, 0));
				} else if (hp < (iHp * 0.25f) && hp >= 1.0f) {
					boss.setFillColor(sf::Color::Red);
				} else if (hp < 1) {
					return true;
				}
			}
		}
		return false;
	}
	// Getters
	int getHp() const {
		return hp;
	}
	// Draw
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(boss, states);
	}
private:

private:
	sf::CircleShape boss;
	int iHp;
	int hp;
	float speed;
	bool goRight;
	sf::Time timeBank;
	float fireRate;
};