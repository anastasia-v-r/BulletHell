#include "MenuScreen.hpp"
#include <SFML/Graphics.hpp>
#include <game/game.hpp>
#include <player/player.hpp>
#include <customObjects/menuButton.hpp>

void MenuScreen::run(sf::RenderWindow& window, GameState& state, Player& plr) {

	enum selection {
		Play,
		Profile,
		Settings,
		Exit,
		Nothing
	};
	selection hoveredSelection = selection::Nothing;
	selection enteredSelection = selection::Nothing;
	
	std::vector<sf::Drawable*> screenElements;
	std::vector<menuButton> buttons;
	
	bool exiting = false;

	sf::Texture bg;
	if (bg.loadFromFile("assets/mainMenu/menuBackground.png") != true) {
		return;
	}
	sf::Sprite menuBg(bg);
	screenElements.push_back(&menuBg);
	
	menuButton exitButton("Exit", sf::Vector2f(200, 100), sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 5) * 4));
	screenElements.push_back(&exitButton);
	buttons.push_back(exitButton);
	
	menuButton playButton("Play", sf::Vector2f(200, 100), sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 5) * 2));
	screenElements.push_back(&playButton);
	buttons.push_back(playButton);

	sf::CircleShape activeButton(10);
	activeButton.setFillColor(sf::Color::Red);
	activeButton.setOrigin(10 / 2, 10 / 2);
	activeButton.setPosition(((exitButton.getPos().x) - (exitButton.getSize().x / 2) - 10), (exitButton.getPos().y) - exitButton.getSize().y / 2);
	screenElements.push_back(&activeButton);
	
	sf::Event evnt;
	while (!exiting) {
		// Event Processor
		while (window.pollEvent(evnt)) {
			switch (evnt.type)
			{
			case sf::Event::KeyPressed: {
				switch (evnt.key.code)
				{
				case sf::Keyboard::Up:
					break;
				case sf::Keyboard::Down:
					if (hoveredSelection < 1) {
					}
					break;
				case sf::Keyboard::Enter:
					enteredSelection = hoveredSelection;
					break;
				case sf::Keyboard::Escape:
					enteredSelection = selection::Exit;
					break;
				}
				break;
			}
			case sf::Event::MouseButtonPressed: {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
				for (auto& element : buttons) {
					if (element.getBounds().contains(mousePosF)) {
						if (element.getName() == "Play") {
							enteredSelection = selection::Play;
						}
						else if (element.getName() == "Exit") {
							enteredSelection = selection::Exit;
						}
					}
				}
				break;
			}
			case sf::Event::MouseMoved: {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
				for (auto& element : buttons) {
					if (element.getBounds().contains(mousePosF)) {
						if (element.getName() == "Play") {
							hoveredSelection = selection::Play;
						}
						else if (element.getName() == "Exit") {
							hoveredSelection = selection::Exit;
						}
					}
				}
				break;
			}
		}
		}
		// Logic
		if (enteredSelection != selection::Nothing) {
			switch (enteredSelection)
			{
			case selection::Play:
				state = GameState::Playing;
				exiting = true;
				break;
			case selection::Exit:
				state = GameState::Exiting;
				exiting = true;
				break;
			}
		}
		// Drawing
		window.clear();
		for (const auto& element : screenElements) {
			window.draw(*element);
		}
		window.display();
	}
}
