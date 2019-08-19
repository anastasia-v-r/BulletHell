#pragma once
#include <SFML/Graphics.hpp>
#include <resourceManager/resourceManager.hpp>
#include <stateManager/stateManager.hpp>
#include <user/user.hpp>

class Game : private sf::NonCopyable
{
private:
	sf::RenderWindow mWindow;
	User mCurrentUser;
	StateManager mStateManager;
	ResourceManager mResourceManager;
	sf::RectangleShape box = sf::RectangleShape(sf::Vector2f(10, 10));

public:
	void run();
	void processEvents();
	void gameLogic();
	void draw();

public:
	Game();
	~Game();

};
