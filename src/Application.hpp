#pragma once
#include "StateManager.hpp"
#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>

enum Dir
{
	None,
	Up,
	Right,
	Down,
	Left
};

class Application
{
public:
	Application();
	void run();
private:
	void HandleInput();
	void UpdateGame();
	void DrawElements();
private:
	sf::RenderWindow mWindow;
	StateManager mStackManager;
	ResourceManager mResourceManager;

	bool exiting = false;
	sf::RectangleShape box = sf::RectangleShape(sf::Vector2f(10, 10));
	Dir direction;
};