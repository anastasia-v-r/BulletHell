#include "Splash.hpp"
#include <SFML/Graphics.hpp>
#include "Globals.hpp"
#include <string>
#include <iostream>

Splash::Splash(sf::Texture& texture)
	: box(texture)
	, cover(sf::Vector2f(GlobalData::TRUE_WIDTH, GlobalData::TRUE_HEIGHT))
	, fadingIn{ true } 
	, timebank{ sf::Time::Zero } {
	this->cover.setFillColor(sf::Color(0, 0, 0, 255));
}

bool Splash::fade(sf::Time elapsedTime) {
	if (this->timebank.asSeconds() > .01f) {
		sf::Color temp = cover.getFillColor();
		if (fadingIn) {
			temp.a--;
			if (temp.a == 1)
				fadingIn = false;
			cover.setFillColor(temp);
		} else {
			temp.a++;
			if (temp.a == 255)
				return false;
			cover.setFillColor(temp);
		}
		timebank = (sf::seconds)(timebank.asSeconds() - .01f);
	} else {
		timebank += elapsedTime;
	}
	return true;
}

void Splash::draw(sf::RenderTarget& window, sf::RenderStates states) const {
	window.draw(box, states);
	window.draw(cover, states);
}