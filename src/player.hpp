#pragma once
#include <SFML/Graphics.hpp>
#include "bullet.hpp"

class Player : public sf::Drawable
{
public:
	// Cons. & Desc.
	Player(sf::VideoMode mode) 
		: player{ sf::Vector2f(20.0f, 20.0f) }
		, hp{ 3 } {
		player.setPosition(mode.width / 2.0f, mode.height / 2.0f);
		player.setFillColor(sf::Color::Green);
	}
	// Processors
	void move(sf::Time elapsedTime, const std::map<std::string, bool>& keyMap) {
		if (keyMap.at("Up"))
			player.move(0, -speed * elapsedTime.asSeconds());
		if (keyMap.at("Right"))
			player.move(speed * elapsedTime.asSeconds(), 0);
		if (keyMap.at("Down"))
			player.move(0, speed * elapsedTime.asSeconds());
		if (keyMap.at("Left"))@
			player.move(-speed * elapsedTime.asSeconds(), 0);
	}
	int dmg() {
		hp--;
		if (hp == 2)
			player.setFillColor(sf::Color(255, 98, 0));
		else if (hp == 1)
			player.setFillColor(sf::Color::Red);
		else
			return true;
		return false;
	}
	// Getters
	const sf::RectangleShape& obj() {
		return player;
	}
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(player, states);
	}
private:

private:
	sf::RectangleShape player;
	int hp;
	int speed;
};

