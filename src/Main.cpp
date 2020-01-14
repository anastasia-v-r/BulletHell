// Includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Globals.hpp"
#include "ResourceManager.hpp"
#include "States/IntroState.hpp"
#include "States/MenuState.hpp"
#include "States/SettingState.hpp"
#include "States/ProfileState.hpp"
#include "States/GameState.hpp"
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <iostream>

//************************
// Function Declarations *
//************************

void ResizeView(const sf::RenderWindow& window, sf::View& view);

int main() {
	// Create Render Window
	auto realmode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(realmode, L"弾幕", sf::Style::Default);

	// Setup View
	sf::View view(sf::Vector2f(GlobalData::TRUE_WIDTH / 2.0f, GlobalData::TRUE_HEIGHT / 2.0f), sf::Vector2f(GlobalData::TRUE_WIDTH, GlobalData::TRUE_HEIGHT));
	ResizeView(window, view);
	window.setView(view);
	window.setPosition(sf::Vector2i(1, 0));
	window.setKeyRepeatEnabled(false);
	
	// Setup clocks
	sf::Clock gameClock;
	sf::Time lastUpdate = sf::Time::Zero;
	std::queue<sf::Time> fps;

	// StateHolder
	std::stack<std::unique_ptr<State>> stateStack;
	std::queue<std::pair<StateChange, StateID>> pendingStackChanges;
	stateStack.push(std::make_unique<IntroState>(pendingStackChanges));

	// Misc Vars
	sf::Event evnt;

	// Run While the window is open
	while (window.isOpen()) {
		// Process Events
		while (window.pollEvent(evnt)) {
			switch (evnt.type)
			{
			case sf::Event::Closed:
				pendingStackChanges.push({ StateChange::WIPE, StateID::INTRO });
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				window.setView(view);
				break;
			default:
				stateStack.top()->input(evnt, window, view);
				break;
			}
		}

		// Update Game
		stateStack.top()->update(gameClock.getElapsedTime() - lastUpdate);
		lastUpdate = gameClock.getElapsedTime();
		
		// Draw objects
		stateStack.top()->draw(window);
		
		// Calculate Fps
		fps.push(gameClock.getElapsedTime());
		while (fps.front() < (gameClock.getElapsedTime() - (sf::seconds)(1)))
			fps.pop();
		window.setTitle(L"『弾幕』 FPS : " + (std::to_wstring(fps.size() / 1)));

		// Process Stack Changes
		while (!pendingStackChanges.empty()) {
			switch (pendingStackChanges.front().first)
			{
			case StateChange::ADD:
				switch (pendingStackChanges.front().second)
				{
				case StateID::INTRO:
					stateStack.push(std::make_unique<IntroState>(pendingStackChanges));
					break;
				case StateID::MENU:
					stateStack.push(std::make_unique<MenuState>(pendingStackChanges));
					break;
				case StateID::SETTING:
					stateStack.push(std::make_unique<SettingState>(pendingStackChanges));
					break;
				case StateID::PROFILE:
					stateStack.push(std::make_unique<ProfileState>(pendingStackChanges));
					break;
				case StateID::GAME:
					stateStack.push(std::make_unique<GameState>(pendingStackChanges));
					break;
				default:
					break;
				}
				break;
			case StateChange::REMOVE:
				while (stateStack.top()->getId() != pendingStackChanges.front().second) {
					stateStack.pop();
				}
				ResourceManager::instance().unloadState();
				break;
			case StateChange::WIPE:
				while (!stateStack.empty()) {
					stateStack.pop();
					ResourceManager::instance().unloadState();
				}
				window.close();
				break;
			}
			pendingStackChanges.pop();
		}
	}
	// Data Saving code
}
//***********************
// Function Definitions *
//***********************  

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
	if ((float)window.getSize().x / (float)window.getSize().y != GlobalData::TRUE_WIDTH / GlobalData::TRUE_WIDTH) {
		std::cout << "NOT 16:9" << std::endl;
		float aspectRatio = (float)window.getSize().x / (float)window.getSize().y;
		if (aspectRatio > GlobalData::TRUE_WIDTH / GlobalData::TRUE_HEIGHT) { // Side bars
			view.setViewport(sf::FloatRect((1.0f - (GlobalData::TRUE_RATIO / aspectRatio)) / 2.0f, 0.0f, GlobalData::TRUE_RATIO / aspectRatio, 1.0f));
		}
		else { // Bars on top and under
			view.setViewport(sf::FloatRect(0.0f, (1.0f - (aspectRatio / GlobalData::TRUE_RATIO)) / 2.0f, 1.0f, aspectRatio / GlobalData::TRUE_RATIO));
		}
	} else {
		view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	}
}
