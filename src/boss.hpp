#pragma once
#include <SFML/Graphics.hpp>
#include "bullet.hpp"
#include <cmath>

class Boss : public sf::Drawable
{
public:
	Boss(sf::VideoMode mode)
		: boss{ 50.0f }
		, hp{ 100 }
		, speed{ 200.0f } 
		, goRight{ true } 
		, fireRate{ 1.0f / 4.0f } 
		, timeBank{ sf::Time::Zero } {
		boss.setPosition(mode.width / 2.0f, 0.0f);
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
			bullets.push_back(Bullet(boss.getPosition() + sf::Vector2f(0.0f, boss.getRadius() * 2), -1.0f, false));
			bullets.push_back(Bullet(boss.getPosition() + sf::Vector2f(boss.getRadius() * 2, boss.getRadius() * 2), -1.0f, false));
			timeBank -= (sf::seconds)(fireRate);
		} else {
			timeBank += elapsedTime;
		}
	}
	bool detectCollide(std::vector<Bullet>& bullets) {
		for (auto& bullet : bullets) {
			if ( std::sqrt(std::pow((boss.getPosition().x - bullet.getPos().x), 2) / std::pow((boss.getPosition().y - bullet.getPos().y), 2)) < (boss.getRadius() + bullet.getRadius()) ) {
				bullet.invalidate();
				hp -= 5;
				if (hp < 75 && hp >= 50) {
					boss.setFillColor(sf::Color::Yellow);
				} else if (hp < 50 && hp >= 25) {
					boss.setFillColor(sf::Color(255, 98, 0));
				} else if (hp < 25 && hp >= 1) {
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
	int hp;
	float speed;
	bool goRight;
	sf::Time timeBank;
	float fireRate;
};