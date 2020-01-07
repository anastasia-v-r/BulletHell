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
	background.setTexture(&ResourceManager::instance().getTexture("Background"));
	buttons.insert({ "Play", Button("Play!", sf::Vector2f(100.0f, 75.0f), {GlobalData::TRUE_WIDTH / 2, GlobalData::TRUE_HEIGHT / 5 * 2}, sf::Color::Red) });
	buttons.insert({ "Settings", Button("Settings", sf::Vector2f(100.0f, 75.0f), {GlobalData::TRUE_WIDTH / 2, GlobalData::TRUE_HEIGHT / 5 * 3}, sf::Color::Blue) });
	buttons.insert({ "Exit", Button("Exit", sf::Vector2f(100.0f, 75.0f), {GlobalData::TRUE_WIDTH / 2, GlobalData::TRUE_HEIGHT / 5 * 4}, sf::Color::Green) });
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
		if (buttons.at("Play").contains(mousePosF)) {
			pendingChanges.push({ StateChange::ADD, StateID::GAME });
		} else if (buttons.at("Settings").contains(mousePosF)) {
			pendingChanges.push({ StateChange::ADD, StateID::SETTING });
		} else if (buttons.at("Exit").contains(mousePosF)) {
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
	for (const auto& button : buttons) {
		window.draw(button.second);
	}
	window.display();
}
