#pragma once
#include "../game.hpp"
#include "../player/player.hpp"

class MenuScreen
{
public:
	void run(sf::RenderWindow&, GameState&, Player&);
};