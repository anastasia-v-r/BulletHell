#include "IntroState.hpp"

IntroState::IntroState(std::queue<std::pair<StateChange, StateID>>& pendingChanges)
	: State(StateID::INTRO, pendingChanges) {

}

void IntroState::update(sf::Time elapsedTime, bool& close) {

}

void IntroState::draw(sf::RenderWindow& window) {
	
}
