#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
constexpr float Pi = 3.14159265;

constexpr float deg_to_rad(float angle_deg) {
	return (angle_deg * Pi) / 180;
}

class Bullet : public sf::Drawable
{
public:
	Bullet(sf::Vector2f, float, float, float, float, float, const sf::Texture&);
	Bullet(sf::Vector2f, float, float, float, const sf::Texture&, bool);
	Bullet(sf::Vector2f, float, float, float, float, float, sf::Color);
	// Getters
	float getRadius() const {
		return bullet.getRadius();
	}
	float getHeight() const {
		return bullet.getPosition().y;
	}
	auto getPos() const {
		return bullet.getPosition();
	}
	bool getVal() const {
		return valid;
	}
	float getDmg() const {
		return dmg;
	}
	// Processors
	void travel(const sf::Time&, sf::Vector2f);
	void invalidate() {
		valid = false;
	}
	// Draw
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(bullet, states);
	}
private:
	sf::CircleShape bullet;
	float speed;
	bool valid;
	sf::Vector2f angle;
	float dir;
	float angularVelocity;
	float dmg;
	bool tracking;
};
