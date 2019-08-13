#include "game.h"
#include "SFML/Graphics.hpp"
#include "gameStates/SplashScreen.h"
#include "gameStates/MenuScreen.h"

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
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop() {
	sf::Event evnt;
	while (_mainWindow.pollEvent(evnt)) {
		switch (_gameState)
		{
			case Game::Splash:
				runSplash();
			case Game::MainMenu:
				runMenu();
		}
	}
}

void Game::runSplash() {
	SplashScreen splashScreen;
	splashScreen.run(_mainWindow);
	_gameState = Game::MainMenu;
}

void Game::runMenu() {
	MenuScreen menuScreen;
	menuScreen.run(_mainWindow);
}

Game::Game(){
	_gameState = Uninitialized;
}

Game::~Game() {

}