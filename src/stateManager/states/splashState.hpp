#pragma once
#include <stateManager/state.hpp>

class SplashState : public State
{
private:
	sf::RectangleShape box = sf::RectangleShape(sf::Vector2f(10, 10));
public:
	virtual void draw(sf::RenderTarget&, sf::RenderStates);
};
