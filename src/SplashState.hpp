#pragma once
#include "State.hpp"
#include <SFML/Graphics.hpp>

class SplashState : public State
{
public:
	SplashState();
	virtual void HandleInput(sf::RenderWindow&) override;
	virtual void UpdateGame(sf::RenderWindow&)  override;
	virtual void DrawElements(sf::RenderWindow&) override;
private:
	sf::RectangleShape splashImage;
	sf::Texture image;
};