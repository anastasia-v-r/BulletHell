#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

// WINDOW AND VIEW DATA

inline const float TRUE_WIDTH = 1920.0f;
inline const float TRUE_HEIGHT = 1080.0f;
inline const float TRUE_RATIO = TRUE_WIDTH / TRUE_HEIGHT;
inline const sf::VideoMode TRUE_MODE(1920.0f, 1080.0f, 32);

// KEYMAP

inline std::map<std::string, bool> keyMap = {
	{"Up", false},
	{"Right", false},
	{"Down", false},
	{"Left", false},
	{"Space", false }
};