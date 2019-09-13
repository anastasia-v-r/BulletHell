#include "GameState.hpp"

GameState::GameState() {
	auto mode = sf::VideoMode::getDesktopMode();
	mKeys = { {"Up", false}, {"Right", false}, {"Down", false}, {"Left", false} };
	mPlayer = sf::RectangleShape(sf::Vector2f(50, 50));
	mPlayerTexture.loadFromFile("assets/GameState/PlayerTexture.png");
	mPlayer.setTexture(&mPlayerTexture);
	mPlayer.setPosition(mode.width / 2, mode.height / 2);
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
		mPlayer.setPosition(mPlayer.getPosition().x, mPlayer.getPosition().y - .1);
	if (mKeys["Right"])
		mPlayer.setPosition(mPlayer.getPosition().x + .1, mPlayer.getPosition().y);
	if (mKeys["Down"])
		mPlayer.setPosition(mPlayer.getPosition().x, mPlayer.getPosition().y + .1);
	if (mKeys["Left"])
		mPlayer.setPosition(mPlayer.getPosition().x - .1, mPlayer.getPosition().y);
}

void GameState::DrawElements(sf::RenderWindow& window) {
	window.clear();
	window.draw(mPlayer);
	window.display();
}