#include "bullet.hpp"
#include <SFML/Graphics.hpp>

Bullet::Bullet(sf::Vector2f pos, float dir, bool plr, float speed, float angVel, float dmg, float size, const sf::Texture& texture)
	: bullet{ size }
	, speed{ speed }
	, player{ plr }
	, valid{ true }
	, dir{ dir }
	, angularVelocity{ angVel }
	, dmg{ dmg } {
	bullet.setTexture(&texture);
	angle = sf::Vector2f((float)std::sin(deg_to_rad(dir)), (float)-std::cos(deg_to_rad(dir)));
	bullet.setOrigin(bullet.getRadius(), bullet.getRadius());
	bullet.setPosition(pos);
}
Bullet::Bullet(sf::Vector2f pos, float dir, bool plr, float speed, float angVel, float dmg, float size)
	: bullet{ size }
	, speed{ speed }
	, player{ plr }
	, valid{ true }
	, dir{ dir }
	, angularVelocity{ angVel }
	, dmg{ dmg } {
	angle = sf::Vector2f((float)std::sin(deg_to_rad(dir)), (float)-std::cos(deg_to_rad(dir)));
	bullet.setOrigin(bullet.getRadius(), bullet.getRadius());
	bullet.setPosition(pos);
	if (plr)
		bullet.setFillColor(sf::Color::Green);
	else
		bullet.setFillColor(sf::Color::Magenta);
}