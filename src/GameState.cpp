#include "GameState.hpp"

GameState::GameState() {
	auto mode = sf::VideoMode::getDesktopMode();
	mKeys = { 
		{"Up", false}, 
		{"Right", false}, 
		{"Down", false}, 
		{"Left", false} 
	};
	screenElements = {
		{"Background", new sf::RectangleShape(sf::Vector2f(mode.width, mode.height))},
		{"Player", new sf::RectangleShape(sf::Vector2f(50, 50))}
	};
	textures = {
		{"Background", new sf::Texture},
		{"Player", new sf::Texture}
	};
	textures["Background"]->loadFromFile("assets/GameState/BackgroundTexture.png");
	textures["Player"]->loadFromFile("assets/GameState/PlayerTexture.png");
	screenElements["Background"]->setTexture(textures["Background"]);
	screenElements["Player"]->setTexture(textures["Player"]);
	screenElements["Player"]->setPosition(mode.width / 2, mode.height / 2);
}

void GameState::HandleInput(sf::RenderWindow& window) {
	sf::Event evnt;
	while (window.pollEvent(evnt)) {
		switch (evnt.type)
		{
		case sf::Event::KeyPressed:
			switch (evnt.key.code) 
			{
			case sf::Keyboard::W:
			case sf::Keyboard::Up:
				mKeys["Up"] = true;
				break;
			case sf::Keyboard::D:
			case sf::Keyboard::Right:
				mKeys["Right"] = true;
				break;
			case sf::Keyboard::S:
			case sf::Keyboard::Down:
				mKeys["Down"] = true;
				break;
			case sf::Keyboard::A:
			case sf::Keyboard::Left:
				mKeys["Left"] = true;
				break;
			case sf::Keyboard::Escape:
				State::removeState = true;
				break;
			}
			break;
		case sf::Event::KeyReleased:
			switch (evnt.key.code)
			{
			case sf::Keyboard::W:
			case sf::Keyboard::Up:
				mKeys["Up"] = false;
				break;
			case sf::Keyboard::D:
			case sf::Keyboard::Right:
				mKeys["Right"] = false;
				break;
			case sf::Keyboard::S:
			case sf::Keyboard::Down:
				mKeys["Down"] = false;
				break;
			case sf::Keyboard::A:
			case sf::Keyboard::Left:
				mKeys["Left"] = false;
				break;
			}
			break;
		}
	}
}

void GameState::UpdateGame(sf::RenderWindow& window) {
	if (mKeys["Up"])
		screenElements["Player"]->setPosition(screenElements["Player"]->getPosition().x, screenElements["Player"]->getPosition().y - .1);
	if (mKeys["Right"])
		screenElements["Player"]->setPosition(screenElements["Player"]->getPosition().x + .1, screenElements["Player"]->getPosition().y);
	if (mKeys["Down"])
		screenElements["Player"]->setPosition(screenElements["Player"]->getPosition().x, screenElements["Player"]->getPosition().y + .1);
	if (mKeys["Left"])
		screenElements["Player"]->setPosition(screenElements["Player"]->getPosition().x - .1, screenElements["Player"]->getPosition().y);
}

void GameState::DrawElements(sf::RenderWindow& window) {
	window.clear();
	for (const auto& element : screenElements) {
		window.draw(*element.second);
	}
	window.display();
}