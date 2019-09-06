#include "SplashState.hpp"

SplashState::SplashState() {
	bg.loadFromFile("assets/splashScreen/BulletHellSplash.png");
}

void SplashState::HandleInput() {

}

void SplashState::UpdateGame() {

}

void SplashState::DrawElements(sf::RenderWindow& window) {
	window.clear();
	window.draw(box);
	window.display();
}