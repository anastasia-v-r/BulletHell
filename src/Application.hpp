#pragma once
// #include "StateManager.hpp"
// #include "ResourceManager.hpp"
#include "State.hpp"
#include "SplashState.hpp"
#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <stack>

class Application
{
public:
	Application(sf::VideoMode);
	void run();
private:

private:
	sf::RenderWindow mWindow;
	std::stack<State*> mStates;

	bool exiting;
};