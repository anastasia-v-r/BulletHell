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
		{"Background", new sf::RectangleShape(sf::Vector2f((float)mode.width, (float)mode.height))},
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
	screenElements["Player"]->setPosition(mode.width / 2.0f, mode.height / 2.0f);
}

void GameState::HandleInput(sf::RenderWindow& window) {
	sf::Event evnt;
	while (window.pollEvent(evnt)) {
		switch (evnt.type)
		{
		case sf::Event::KeyPressed:
			switch (evnt.key.code) 
			{
			case sf::Keyboard::Escape:
				State::removeState = true;
				break;
			default:
				processKeys(evnt.key.code, true);
				break;
			}
			break;
		case sf::Event::KeyReleased:
			processKeys(evnt.key.code, false);
			break;
		case sf::Event::Closed:
			State::wipeStates = true;
			break;
		}
	}
}

void GameState::UpdateGame(sf::RenderWindow& window) {
	if (mKeys["Up"])
		screenElements["Player"]->move( 0.0f, -0.1f );
	if (mKeys["Right"])
		screenElements["Player"]->move( 0.1f, 0.0f );
	if (mKeys["Down"])
		screenElements["Player"]->move( 0.0f, 0.1f );
	if (mKeys["Left"])
		screenElements["Player"]->move( -0.1f, 0.0f );
}

void GameState::DrawElements(sf::RenderWindow& window) {
	window.clear();
	for (const auto& element : screenElements) {
		window.draw(*element.second);
	}
	window.display();
}

void GameState::processKeys(sf::Keyboard::Key key, bool pressed) {
	switch (key)
	{
	case sf::Keyboard::W:
	case sf::Keyboard::Up:
		mKeys["Up"] = pressed;
		break;
	case sf::Keyboard::D:
	case sf::Keyboard::Right:
		mKeys["Right"] = pressed;
		break;
	case sf::Keyboard::S:
	case sf::Keyboard::Down:
		mKeys["Down"] = pressed;
		break;
	case sf::Keyboard::A:
	case sf::Keyboard::Left:
		mKeys["Left"] = pressed;
		break;
	}
}