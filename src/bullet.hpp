#pragma once

class Bullet : public sf::Drawable
{
public:
	Bullet(sf::Vector2f pos)
		: bullet{ sf::RectangleShape(sf::Vector2f(10.0f, 10.0f)) }
		, speed{ 750.0f } {
		bullet.setPosition(pos);
		bullet.setFillColor(sf::Color::Green);
	}
	void travel(const sf::Time& time) {
		bullet.move(0.0f, -speed * time.asSeconds());
	}
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(bullet, states);
	}
private:
	sf::RectangleShape bullet;
	float speed;
};
