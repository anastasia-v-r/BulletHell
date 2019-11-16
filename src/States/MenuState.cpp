#include "MenuState.hpp"

MenuState::MenuState(std::queue<std::pair<StateChange, StateID>>& pendingChanges)
	: State(StateID::MENU, pendingChanges)
	, button(sf::Vector2f(100.0f, 100.0f)) {

}

void MenuState::input(sf::Event evnt, bool& close, sf::RenderWindow& window, sf::View& view) {
	switch (evnt.type)
	{
	case sf::Event::MouseButtonPressed: {
		sf::Vector2f mousePosF = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
		}
	}
}

void MenuState::update(sf::Time elapsedTime, bool& close) {

}

void MenuState::draw(sf::RenderWindow& window) {
	window.draw(button);
}
