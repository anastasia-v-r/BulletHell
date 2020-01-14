#include "MenuState.hpp"
#include "Entities/Button.hpp"
#include "Globals.hpp"
#include "ResourceManager.hpp"

MenuState::MenuState(std::queue<std::pair<StateChange, StateID>>& pendingChanges)
	: State(StateID::MENU, pendingChanges)
	, background(sf::Vector2f({GlobalData::TRUE_WIDTH, GlobalData::TRUE_HEIGHT})) {
	ResourceManager::instance().loadState({
		{"Background", "assets/mainMenu/menuBackground.png"}
	});
	background.setTexture(&ResourceManager::instance().getTexture("Background")); // TODO : Move to UIElement subcontainer
	m_UIMng.addElement({ "Play", new Button("Play!", sf::Vector2f(100.0f, 75.0f), {GlobalData::TRUE_WIDTH / 2, GlobalData::TRUE_HEIGHT / 6 * 2}, sf::Color::Red) });
	m_UIMng.addElement({ "Settings", new Button("Settings", sf::Vector2f(100.0f, 75.0f), {GlobalData::TRUE_WIDTH / 2, GlobalData::TRUE_HEIGHT / 6 * 3}, sf::Color::Blue) });
	m_UIMng.addElement({ "Profile", new Button("Profile", sf::Vector2f(100.0f, 75.0f), {GlobalData::TRUE_WIDTH / 2, GlobalData::TRUE_HEIGHT / 6 * 4}, sf::Color::Yellow) });
	m_UIMng.addElement({ "Exit", new Button("Exit", sf::Vector2f(100.0f, 75.0f), {GlobalData::TRUE_WIDTH / 2, GlobalData::TRUE_HEIGHT / 6 * 5}, sf::Color::Green) });
}

void MenuState::input(sf::Event evnt, sf::RenderWindow& window, sf::View& view) {
	switch (evnt.type)
	{
	case sf::Event::KeyPressed:
		switch (evnt.key.code)
		{
		case sf::Keyboard::Escape:
			pendingChanges.push({StateChange::REMOVE, StateID::INTRO});
			break;
		default:
			break;
		}
		break;
	case sf::Event::MouseButtonPressed: {
		sf::Vector2f mousePosF = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
		if (m_UIMng.getElement("Play").contains(mousePosF)) {
			pendingChanges.push({ StateChange::ADD, StateID::GAME });
		} else if (m_UIMng.getElement("Settings").contains(mousePosF)) {
			pendingChanges.push({ StateChange::ADD, StateID::SETTING });
		} else if (m_UIMng.getElement("Profile").contains(mousePosF)) {
			pendingChanges.push({ StateChange::ADD, StateID::PROFILE });
		} else if (m_UIMng.getElement("Exit").contains(mousePosF)) {
			pendingChanges.push({ StateChange::WIPE, StateID::INTRO });
		}
		}
		break;
	}
}

void MenuState::update(sf::Time elapsedTime) {

}

void MenuState::draw(sf::RenderWindow& window) {
	window.clear();
	window.draw(background);
	window.draw(m_UIMng);
	window.display();
}
