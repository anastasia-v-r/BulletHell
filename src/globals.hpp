#pragma once

// WINDOW AND VIEW DATA

static const float TRUE_WIDTH = 1920.0f;
static const float TRUE_HEIGHT = 1080.0f;
static const float TRUE_RATIO = TRUE_WIDTH / TRUE_HEIGHT;
static int xOffset = 0;
static int yOffset = 0;
static const sf::VideoMode TRUE_MODE(1920.0f, 1080.0f, 32);

// KEYMAP

static std::map<std::string, bool> keyMap = {
	{"Up", false},
	{"Right", false},
	{"Down", false},
	{"Left", false},
	{"Space", false }
};