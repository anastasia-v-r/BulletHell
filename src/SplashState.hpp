#pragma once
#include "State.hpp"
#include <SFML/Graphics.hpp>

class SplashState : public State
{
public:
	SplashState();
	virtual void HandleInput() override;
	virtual void UpdateGame()  override;
	virtual void DrawElements(sf::RenderWindow&) override;
private:

private:
	sf::Image bg;
	sf::RectangleShape box = sf::RectangleShape(sf::Vector2f(10, 10));
};