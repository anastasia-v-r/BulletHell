#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

namespace GlobalData {

	// WINDOW AND VIEW DATA

	inline const float TRUE_WIDTH = 1920.0f;
	inline const float TRUE_HEIGHT = 1080.0f;
	inline const float TRUE_RATIO = TRUE_WIDTH / TRUE_HEIGHT;
	inline const sf::VideoMode TRUE_MODE(1920U, 1080U, 32U);

	// GLOBAL RESOURCES // TODO: Setup a resource manager to hold all of this
	inline sf::Font font;
}