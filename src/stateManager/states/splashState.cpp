#include "splashState.hpp"
#include <SFML/Graphics.hpp>

void SplashState::events() {

}

void SplashState::logic() {

}

void  SplashState::draw(sf::RenderTarget& window, sf::RenderStates states){
	window.draw(box, states);
}