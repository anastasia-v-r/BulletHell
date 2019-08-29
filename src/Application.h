#pragma once

#include <stateManager/StateManager.h>
#include <SFML/Graphics.hpp>

class Application
{
private: // Variables
	static const sf::Time FrameTime;
	sf::RenderWindow mWindow;

	
public: // Public funcs
	Application();
	void runApp();
private: // Interal funcs
	void processInput();
	void updateGame(sf::Time);
	void renderGame();
};