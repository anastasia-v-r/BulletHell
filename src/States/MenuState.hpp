#pragma once
#include "State.hpp"
#include "Entities/Button.hpp"
#include <SFML/Graphics.hpp>
#include <map>

class MenuState : public State
{
public:
	MenuState(std::queue<std::pair<StateChange, StateID>>& /* pendingChanges */);
	void input(sf::Event /* evnt */, bool& /* close */, sf::RenderWindow& /* window */, sf::View& /* view */) override;
	void update(sf::Time /* elapsedTime */, bool& /* close */) override;
	void draw(sf::RenderWindow& /* window */) override;
private:
	std::map<std::string, Button> buttons;
	sf::RectangleShape button;
	sf::Text text;
};