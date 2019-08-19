#include "game.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <game/game.hpp>
#include <gameStates/SplashScreen.hpp>
#include <gameStates/MenuScreen.hpp>

void Game::Start() {

	GameLoop();

	_mainWindow.close();
}

void Game::GameLoop() {
	while (running) {
		switch (_gameState)
		{
			case GameState::Splash:
				SplashScreen splashScreen;
				splashScreen.run(_mainWindow);
				_gameState = GameState::MainMenu;
			case GameState::MainMenu:
				MenuScreen menuScreen;
				menuScreen.run(_mainWindow, _gameState, player);
				break;
			case GameState::Playing:

			case GameState::Exiting:
				std::cout << "Exiting \n";
				running = false;
				break;
		}
	}
}

Game::~Game() {

}