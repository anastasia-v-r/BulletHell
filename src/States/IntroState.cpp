#include "IntroState.hpp"
#include "Globals.hpp"
#include <iostream>

IntroState::IntroState(std::queue<std::pair<StateChange, StateID>>& pendingChanges)
	: State(StateID::INTRO, pendingChanges)
	, button(sf::Vector2f(100.0f, 100.0f)) {
	button.setPosition(sf::Vector2f(GlobalData::TRUE_WIDTH / 3, GlobalData::TRUE_HEIGHT / 3));
	button.setFillColor(sf::Color::Yellow);
	if (!font.loadFromFile("assets/Global/font/OpenSans-Regular.ttf"))
			std::cout << "Font Failed to load" << std::endl;
	sf::Text text("Intro!", font, 30);
	std::cout << (std::string)text.getString() << std::endl;
	text.setPosition(sf::Vector2f(GlobalData::TRUE_WIDTH / 2, GlobalData::TRUE_HEIGHT / 2));
}

void IntroState::input(sf::Event evnt, bool& close, sf::RenderWindow& window, sf::View& view) {
	switch (evnt.type)
	{
	case sf::Event::KeyPressed:
		if (evnt.key.code == sf::Keyboard::Escape) {
			close = true;
		}
		break;
	case sf::Event::MouseButtonPressed: {
		sf::Vector2f mousePosF = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
		if (button.getGlobalBounds().contains(mousePosF)) {
			pendingChanges.push({ StateChange::ADD, StateID::GAME });
		}
	}
	default:
		break;
	}
}

void IntroState::update(sf::Time elapsedTime, bool& close) {

}

void IntroState::draw(sf::RenderWindow& window) {
	window.clear();
	window.draw(button);
	window.draw(text);
	window.display();
}
