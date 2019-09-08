#include "Application.hpp"
#include <iostream>

Application::Application() {
	auto mode = sf::VideoMode::getDesktopMode();
	mode.height += 1;
	mWindow.create(mode, "BulletHell", sf::Style::Default);
	direction = Dir::None;
}

void Application::run() {
	while (!exiting) {
		HandleInput();
		UpdateGame();
		DrawElements();
	}
}

void Application::HandleInput() {
	sf::Event evnt;
	while (mWindow.pollEvent(evnt)) {
		switch (evnt.type)
		{
		case sf::Event::KeyPressed:
			std::cout << evnt.key.code << std::endl;
			switch (evnt.key.code) {
			case sf::Keyboard::W:
				std::cout << "W" << std::endl;
				direction = Dir::Up;
				break;
			case sf::Keyboard::D:
				std::cout << "D" << std::endl;
				direction = Dir::Right;
				break;
			case sf::Keyboard::S:
				std::cout << "S" << std::endl;
				direction = Dir::Down;
				break;
			case sf::Keyboard::A:
				std::cout << "A" << std::endl;
				direction = Dir::Left;
				break;
			case sf::Keyboard::Escape:
				exiting = true;
				break;
			}
			break;
		case sf::Event::KeyReleased:
			std::cout << "None" << std::endl;
			direction = Dir::None;
			break;
		case sf::Event::Closed:
			exiting = true;
			break;
		default:
			break;
		}
	}
}

void Application::UpdateGame() {
	switch (direction)
	{
	case None:
		break;
	case Up:
		box.setPosition(box.getPosition().x, box.getPosition().y - .1);
		break;
	case Right:
		box.setPosition(box.getPosition().x + .1, box.getPosition().y);
		break;
	case Down:
		box.setPosition(box.getPosition().x, box.getPosition().y + .1);
		break;
	case Left:
		box.setPosition(box.getPosition().x - .1, box.getPosition().y);
		break;
	default:
		break;
	}
}

void Application::DrawElements() {
	mWindow.clear();
	mWindow.draw(box);
	mWindow.display();
}