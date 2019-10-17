#pragma once

class Bullet : public sf::Drawable
{
public:
	Bullet(sf::Vector2f pos, int dir, bool plr)
		: bullet{ sf::RectangleShape(sf::Vector2f(20.0f, 20.0f)) }
		, speed{ 750.0f }
		, direction{ dir } 
		, player{ plr }
		, valid{ true } {
		bullet.setPosition(pos);
		bullet.setFillColor(sf::Color::Green);
	}
	// Getters
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
		bullet.move(0.0f, direction * (-speed * time.asSeconds()));
	}
	void invalidate() {
		valid = false;
	}
	// Draw
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(bullet, states);
	}
private:
	sf::RectangleShape bullet;
	float speed;
	int direction;
	bool player;
	bool valid;
};
