#include "game.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "gameStates/SplashScreen.hpp"
#include "gameStates/MenuScreen.hpp"

void Game::Start() {
	if (_gameState != Uninitialized)
		return;
	auto mode = sf::VideoMode::getDesktopMode();
	mode.height += 1;
	_mainWindow.create(mode, "BulletHell!", sf::Style::None);
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
	while (true) {
		switch (_gameState)
		{
			case GameState::Splash:
				runSplash();
			case GameState::MainMenu:
				runMenu();
			case GameState::Exiting:
				runCleanup();
				break;
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

void Game::runCleanup() {
	std::cout << "Exiting \n";
}

Game::~Game() {

}