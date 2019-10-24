#include "bullet.hpp"
#include <SFML/Graphics.hpp>

Bullet::Bullet(sf::Vector2f pos, float dir, float speed, float angVel, float dmg, float size, const sf::Texture& texture)
	: bullet{ size }
	, speed{ speed }
	, valid{ true }
	, dir{ dir }
	, angularVelocity{ angVel }
	, dmg{ dmg } 
	, tracking{ false } {
	bullet.setTexture(&texture);
	angle = sf::Vector2f((float)std::sin(deg_to_rad(dir)), (float)-std::cos(deg_to_rad(dir)));
	bullet.setOrigin(bullet.getRadius(), bullet.getRadius());
	bullet.setPosition(pos);
}
Bullet::Bullet(sf::Vector2f pos, float speed, float dmg, float size, const sf::Texture& texture, bool track)
	: bullet{ size }
	, speed{ speed }
	, valid{ true }
	, dir{ 0.0f }
	, angularVelocity{ 0.0f }
	, dmg{ dmg }
	, tracking{ track } {
	bullet.setTexture(&texture);
	angle = sf::Vector2f((float)std::sin(deg_to_rad(dir)), (float)-std::cos(deg_to_rad(dir)));
	bullet.setOrigin(bullet.getRadius(), bullet.getRadius());
	bullet.setPosition(pos);
}
Bullet::Bullet(sf::Vector2f pos, float dir, float speed, float angVel, float dmg, float size)
	: bullet{ size }
	, speed{ speed }
	, valid{ true }
	, dir{ dir }
	, angularVelocity{ angVel }
	, dmg{ dmg } 
	, tracking{ false } {
	angle = sf::Vector2f((float)std::sin(deg_to_rad(dir)), (float)-std::cos(deg_to_rad(dir)));
	bullet.setOrigin(bullet.getRadius(), bullet.getRadius());
	bullet.setPosition(pos);
	bullet.setFillColor(sf::Color::Magenta);
}