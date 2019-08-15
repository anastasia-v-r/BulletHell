#include "game.hpp"
#include <SFML/Graphics.hpp>
#include "gameStates/SplashScreen.hpp"
#include "gameStates/MenuScreen.hpp"

void Game::Start() {
	if (_gameState != Uninitialized)
		return;
	_mainWindow.create(sf::VideoMode(1921, 1080, 32), "BulletHell!", sf::Style::None);
	_gameState = Splash;

	while (!IsExiting()) {
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == GameState::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop() {
	sf::Event evnt;
	while (_mainWindow.pollEvent(evnt)) {
		switch (_gameState)
		{
			case GameState::Splash:
				runSplash();
			case GameState::MainMenu:
				runMenu();
		}
	}
}

void Game::runSplash() {
	SplashScreen splashScreen;
	splashScreen.run(_mainWindow);
	_gameState = GameState::MainMenu;
}

void Game::runMenu() {
	MenuScreen menuScreen;
	menuScreen.run(_mainWindow, _gameState, player);
}

Game::~Game() {

}