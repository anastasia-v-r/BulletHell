#include "splashState.hpp"
#include <SFML/Graphics.hpp>

void  SplashState::draw(sf::RenderTarget& window, sf::RenderStates states){
	window.draw(box, states);
}