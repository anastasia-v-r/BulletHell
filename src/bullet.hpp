#pragma once
#include <cmath>
#include <iostream>
#define M_PI 3.14159265
#define DEG2RAD(angleDegrees) (angleDegrees * M_PI / 180.0)
class Bullet : public sf::Drawable
{
public:
	Bullet(sf::Vector2f pos, float dir, bool plr, float speed, float angVel)
		: bullet{ 20.0f }
		, speed{ speed }
		, player{ plr }
		, valid{ true }
		, dir{ dir }
		, angularVelocity{ angVel } {
		angle = sf::Vector2f((float)std::sin(DEG2RAD(dir)), (float)-std::cos(DEG2RAD(dir)));
		bullet.setOrigin(bullet.getRadius(), bullet.getRadius());
		bullet.setPosition(pos);
		if (plr)
			bullet.setFillColor(sf::Color::Green);
		else
			bullet.setFillColor(sf::Color::Magenta);
	}
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
	bool getPlr() const {
		return player;
	}
	bool getVal() const {
		return valid;
	}
	// Processors
	void travel(const sf::Time& time) {
		bullet.move(angle * speed * time.asSeconds());
		dir += (angularVelocity * time.asSeconds());
		angle = sf::Vector2f((float)std::sin(DEG2RAD(dir)), (float)-std::cos(DEG2RAD(dir)));
	}
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
	bool player;
	bool valid;
	sf::Vector2f angle;
	float dir;
	float angularVelocity;
};
