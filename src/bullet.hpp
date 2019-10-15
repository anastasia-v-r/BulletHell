#pragma once

class Bullet : public sf::Drawable
{
public:
	Bullet(sf::Vector2f pos)
		: bullet{ sf::RectangleShape(sf::Vector2f(10.0f, 10.0f)) } {
		bullet.setPosition(pos);
		bullet.setFillColor(sf::Color::Green);
	}
	void travel() {
		bullet.move(0.0f, -1.0f);
	}
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(bullet, states);
	}
private:
	sf::RectangleShape bullet;
};
