#pragma once
#include "State.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Button.hpp"

class ProfileState : public State
{
public:
	ProfileState(std::queue<std::pair<StateChange, StateID>>& pendingChanges);
	void input(sf::Event evnt, sf::RenderWindow& window, sf::View& view) override;
	void update(sf::Time elapsedTime) override;
	void draw(sf::RenderWindow& window) override;
private:
	sf::RectangleShape background;
};