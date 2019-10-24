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
Bullet::Bullet(sf::Vector2f pos, float dir, float speed, float angVel, float dmg, float size, sf::Color color)
	: bullet{ size }
	, speed{ speed }
	, valid{ true }
	, dir{ dir }
	, angularVelocity{ angVel }
	, dmg{ dmg } 
	, tracking{ false } {
	angle = sf::Vector2f((float)std::sin(deg_to_rad(dir)), (float)-std::cos(deg_to_rad(dir)));
	bullet.setFillColor(color);
	bullet.setOrigin(bullet.getRadius(), bullet.getRadius());
	bullet.setPosition(pos);
	bullet.setFillColor(sf::Color::Magenta);
}

void Bullet::travel(const sf::Time& time, sf::Vector2f bosspos) {
	if (!tracking) {
		bullet.move(angle * speed * time.asSeconds());
		dir += (angularVelocity * time.asSeconds());
		angle = sf::Vector2f((float)std::sin(deg_to_rad(dir)), (float)-std::cos(deg_to_rad(dir)));
	}
	else {
		bullet.rotate(360 * time.asSeconds());
		auto diff = (bosspos - bullet.getPosition());
		diff /= std::sqrt((diff.x * diff.x) + (diff.y * diff.y));
		bullet.move(diff * speed * time.asSeconds());
	}
}