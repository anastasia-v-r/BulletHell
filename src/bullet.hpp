#pragma once

class Bullet : public sf::Drawable
{
public:
	Bullet(sf::Vector2f pos, int dir)
		: bullet{ sf::RectangleShape(sf::Vector2f(10.0f, 10.0f)) }
		, speed{ 750.0f }
		, direction{ dir } {
		bullet.setPosition(pos);
		bullet.setFillColor(sf::Color::Green);
	}
	// Getters
	float getHeight() {
		return bullet.getPosition().y;
	}
	// Processors
	void travel(const sf::Time& time) {
		bullet.move(0.0f, direction * (-speed * time.asSeconds()));
	}
	// Draw
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(bullet, states);
	}
private:
	sf::RectangleShape bullet;
	float speed;
	int direction;
};
