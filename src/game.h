#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


class Game 
{

public:
	void Start();

private:
	enum GameState {
		Uninitialized, Splash, MainMenu, 
		Playing, Paused, Exiting
	};
	GameState _gameState;
	sf::RenderWindow _mainWindow;

	bool IsExiting();
	void GameLoop();

	void runSplash();
	void runMenu();

public:
	Game();
	~Game();
};