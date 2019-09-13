#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum StateEnum
{
	None,
	Splash,
	Menu,
	Game
};

class State
{
public:
	virtual void HandleInput(sf::RenderWindow&) = 0;
	virtual void UpdateGame(sf::RenderWindow&) = 0;
	virtual void DrawElements(sf::RenderWindow&) = 0;
private:

public:
	static bool removeState;
	static bool wipeStates;
	static bool addState;
	static StateEnum nextState;
};
