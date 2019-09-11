#pragma once
#include "StateManager.hpp"
#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>

class Application
{
public:
	Application(sf::VideoMode);
	void run();
private:

private:
	sf::RenderWindow mWindow;
	StateManager mStackManager;
	ResourceManager mResourceManager;

	bool exiting;
};