#pragma once
#include <SFML/Graphics.hpp>
#include "bullet.hpp"

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
	}
	// Processors
	void move(sf::Time elapsedTime, const std::map<std::string, bool>& keyMap) {
		if (keyMap.at("Up"))
			player.move(0, -speed * elapsedTime.asSeconds());
		if (keyMap.at("Right"))
			player.move(speed * elapsedTime.asSeconds(), 0);
		if (keyMap.at("Down"))
			player.move(0, speed * elapsedTime.asSeconds());
		if (keyMap.at("Left"))
			player.move(-speed * elapsedTime.asSeconds(), 0);
	}
	void fire(const sf::Time& elapsedTime, std::vector<Bullet>& bullets, bool key) {
		if (key) {
			if (timeBank.asSeconds() > fireRate) {
				bullets.push_back(Bullet(sf::Vector2f(player.getPosition().x, player.getPosition().y + player.getRadius()), 0.0f, true, 1000.0f));
				timeBank -= (sf::seconds)(fireRate);
			}
			else {
				timeBank += elapsedTime;
			}
		} else {
			if (timeBank >= (sf::seconds)(fireRate * 2.0f)) {
				timeBank -= (sf::seconds)(fireRate);
			} else if (timeBank >= (sf::seconds)(fireRate)) {
				timeBank = (sf::seconds)(fireRate);
			} else {
				timeBank = sf::Time::Zero;
			}
		}
	}
	bool detectCollide(std::vector<Bullet>& bullets) {
		auto [x2, y2] = player.getPosition();
		float pRad = player.getRadius();
		for (auto& bullet : bullets) {
			auto [x1, y1] = bullet.getPos();
			if ( std::sqrt(std::pow(y2 - y1, 2) + std::pow(x2 - x1, 2)) < (pRad + bullet.getRadius()) ) {
				hp--;
				bullets.clear();
				if (hp == 2) {
					player.setFillColor(sf::Color(255, 98, 0));
					return false;
				} else if (hp == 1) {
					player.setFillColor(sf::Color::Red);
					return false;
				} else {
					return true;
				}
			}
		}
		return false;
	}
	// Getters
	// Draw
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(player, states);
	}
private:

private:
	sf::CircleShape player;
	int hp;
	float speed;
	sf::Time timeBank;
	float fireRate;
};

