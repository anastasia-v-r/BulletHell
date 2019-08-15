#include "../game.hpp"
#include <SFML/Graphics.hpp>
#include "MenuScreen.hpp"
#include "../player/player.hpp"

void MenuScreen::run(sf::RenderWindow& window, GameState& state, Player& plr) {
	bool accBoxActive = false;
	sf::Texture pfpT;
	sf::RectangleShape pfp(sf::Vector2f(200, 200));
	pfp.setPosition(500, 500);
	sf::RectangleShape rect(sf::Vector2f(400, 200));
	rect.setPosition(1000, 500);
	sf::RectangleShape accountButton(sf::Vector2f(400, 200));
	accountButton.setPosition(500, 250);
	sf::Font agencyFont;
	if (!agencyFont.loadFromFile("C:/Windows/Fonts/AGENCYB.TTF"));
	sf::Text accountText("", agencyFont, 20);
	accountText.setPosition(accountButton.getPosition().x, accountButton.getPosition().y);
	accountText.setColor(sf::Color::Green);
	sf::String accountTextS;
	
	sf::Event evnt;
	while (true) {
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::TextEntered) {
				if (accBoxActive) {
					if (evnt.text.unicode == '\b') {
						accountTextS.erase(accountTextS.getSize() - 1, 1);
						accountText.setString(accountTextS);
					}
					else if (evnt.text.unicode < 128) {
						accountTextS += evnt.text.unicode;
						accountText.setString(accountTextS);
					}
				}
				rect.setFillColor(sf::Color::Blue);
			} else if (evnt.type == sf::Event::KeyPressed) {
				if (evnt.key.code == sf::Keyboard::Escape) {
					state = Exiting;
					return;
				} else if (evnt.key.code == sf::Keyboard::Enter) {
					std::string s = accountTextS;
					plr.loadPlayer(s);
					pfpT.loadFromImage(*plr.getPlrPfp());
					pfp.setTexture(&pfpT);
				}
			} else if (evnt.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
				if (rect.getGlobalBounds().contains(mousePosF)) {
					rect.setFillColor(sf::Color::Red);
					accBoxActive = false;
				} else if (accountButton.getGlobalBounds().contains(mousePosF)) {
					accBoxActive = true;
				} else {
					accBoxActive = false;
				}
			}
		}
		window.clear();
		window.draw(rect);
		window.draw(accountButton);
		window.draw(accountText);
		window.draw(pfp);
		window.display();
	}
}