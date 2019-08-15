#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player/player.hpp"

enum GameState {
	Uninitialized, Splash, MainMenu,
	Playing, Paused, Exiting
};

class Game 
{

public:
	void Start();
	
private:
	
	Player player;
	GameState _gameState;
	sf::RenderWindow _mainWindow;

	bool IsExiting();
	void GameLoop();

	void runSplash();
	void runMenu();

public:
	Game() {
		_gameState = { Uninitialized };
		_mainWindow.create(sf::VideoMode(1600, 900, 32), "BulletHell!", sf::Style::None);
	};
	~Game();
};