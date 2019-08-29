#pragma once
#include <>

class State
{
private:

public:
	virtual void handleInput() = 0;
	virtual void updateGame() = 0;
	virtual void renderGame(sf::RenderTarget&, sf::RenderStates) = 0;
};