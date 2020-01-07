#pragma once
#include "State.hpp"
#include "Entities/Button.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <stack>

class MenuState : public State
{
public:
	MenuState(std::queue<std::pair<StateChange, StateID>>& pendingChanges);
	void input(sf::Event evnt, sf::RenderWindow& window, sf::View& view) override;
	void update(sf::Time elapsedTime) override;
	void draw(sf::RenderWindow& window) override;
private:
	std::map<std::string, Button> buttons;
	sf::RectangleShape background;
};