#pragma once
#include "State.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class GameState : public State
{
public:
	GameState();
	virtual void HandleInput(sf::RenderWindow&) override;
	virtual void UpdateGame(sf::RenderWindow&)  override;
	virtual void DrawElements(sf::RenderWindow&) override;
private:

private:
	sf::RectangleShape mPlayer;
	sf::Texture mPlayerTexture;
	std::map<std::string, bool> mKeys;
};