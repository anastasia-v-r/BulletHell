#include "SettingState.hpp"
#include "ResourceManager.hpp"
#include "Globals.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>

SettingState::SettingState(std::queue<std::pair<StateChange, StateID>>& pendingChanges)
	: State(StateID::SETTING, pendingChanges)
	, background(sf::Vector2f({ GlobalData::TRUE_WIDTH, GlobalData::TRUE_HEIGHT })) {
	buttons.insert({"Exit", Button("Exit", sf::Vector2f(100.0f, 75.0f), {GlobalData::TRUE_WIDTH / 2, GlobalData::TRUE_HEIGHT / 5 * 2}, sf::Color::Red) });
}

void SettingState::input(sf::Event evnt, sf::RenderWindow& window, sf::View& view) {
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
		if (buttons.at("Exit").contains(mousePosF)) {
			pendingChanges.push({ StateChange::REMOVE, StateID::MENU });
		}
		}
		break;
	}
}

void SettingState::update(sf::Time elapsedTime) {

}

void SettingState::draw(sf::RenderWindow& window) {
	window.clear();
	window.draw(background);
	for (const auto& button : buttons) {
		window.draw(button.second);
	}
	window.display();
}
