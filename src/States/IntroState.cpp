#include "IntroState.hpp"

IntroState::IntroState(std::queue<std::pair<StateChange, StateID>>& pendingChanges)
	: State(StateID::INTRO, pendingChanges) {

}

void IntroState::input(sf::Event evnt, bool& close, sf::RenderWindow& window, sf::View& view) {

}

void IntroState::update(sf::Time elapsedTime, bool& close) {

}

void IntroState::draw(sf::RenderWindow& window) {
	
}
