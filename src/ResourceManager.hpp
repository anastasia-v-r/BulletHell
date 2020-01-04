#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

class ResourceManager
{
public:
	// Access
	static ResourceManager& instance();

	// Accessors
	sf::Font& getFont();
	sf::Texture& getTexture(const std::string id);
	sf::SoundBuffer& getSound(const std::string id);

	// Memory Operations
	void loadState(const std::string assetList);
	void unloadState();

private:
	ResourceManager();

private:
	std::vector<std::unordered_set<std::string>> assetKeys; // used for tracking what assets where loaded by a state
	std::unordered_map<std::string, sf::Texture> textures;
	std::unordered_map<std::string, sf::SoundBuffer> sounds;
	sf::Music current_song;
	sf::Font game_font;

public:
	ResourceManager(ResourceManager const&) = delete;
	void operator=(ResourceManager const&) = delete;

};
