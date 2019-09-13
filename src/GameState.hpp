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
	void processKeys(sf::Keyboard::Key, bool);
private:
	std::map<std::string, sf::RectangleShape*> screenElements;
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, bool> mKeys;
};