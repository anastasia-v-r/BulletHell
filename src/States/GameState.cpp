#include "GameState.hpp"
#include "Globals.hpp"
#include "Entities/Player.hpp"
#include "Entities/Boss.hpp"
#include "Entities/Bullet.hpp"
#include <iostream>

GameState::GameState() 
	: State(StateID::GAME)
	, player(GlobalData::TRUE_MODE)
	, boss(GlobalData::TRUE_MODE) {
	if (!font.loadFromFile("assets/Global/font/OpenSans-Regular.ttf"))
		std::cout << "Font Failed to load" << std::endl;
	sf::Text hp("HP : ", font, 30);
}

void GameState::update(sf::Time elapsedTime) {

}