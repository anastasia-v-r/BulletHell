#include "ProfileState.hpp"
#include "ResourceManager.hpp"
#include "Globals.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>

ProfileState::ProfileState(std::queue<std::pair<StateChange, StateID>>& pendingChanges) 
	: State(StateID::SETTING, pendingChanges)
	, background(sf::Vector2f({ GlobalData::TRUE_WIDTH, GlobalData::TRUE_HEIGHT })) {
	ResourceManager::instance().loadState({
	
	});
	m_UIMng.addElement({ "Exit", new Button("Exit", sf::Vector2f(100.0f, 75.0f), {GlobalData::TRUE_WIDTH / 2, GlobalData::TRUE_HEIGHT / 5 * 2}, sf::Color::Red) }); 
}

void ProfileState::input(sf::Event evnt, sf::RenderWindow& window, sf::View& view) {
	switch (evnt.type)
	{
	case sf::Event::KeyPressed:
		switch (evnt.key.code)
		{
		case sf::Keyboard::Escape:
			pendingChanges.push({ StateChange::REMOVE, StateID::MENU });
			break;
		default:
			break;
		}
		break;
	case sf::Event::MouseButtonPressed: {
		sf::Vector2f mousePosF = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
		if (m_UIMng.getElement("Exit").contains(mousePosF)) {
			pendingChanges.push({ StateChange::REMOVE, StateID::MENU });
		}
		}
		break;
	}
}

void ProfileState::update(sf::Time elapsedTime) {

}

void ProfileState::draw(sf::RenderWindow& window) {
	window.clear();
	window.draw(background);
	window.draw(m_UIMng);
	window.display();
}
