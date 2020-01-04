#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <stdexcept>

ResourceManager& ResourceManager::instance() {
	static ResourceManager s_instance;
	return s_instance;
}

ResourceManager::ResourceManager() {
	game_font.loadFromFile("assets/Global/font/OpenSans-Regular.ttf");
}

sf::Font& ResourceManager::getFont() {
	return game_font;
}

sf::Texture& ResourceManager::getTexture(const std::string id) {
	return textures[id];
}

sf::SoundBuffer& ResourceManager::getSound(const std::string id) {
	return sounds[id];
}

void ResourceManager::loadState(const std::vector<std::pair<std::string, std::string>> assetlist) {
	assetKeys.push_back(std::unordered_set<std::string>());
	for (const auto& asset : assetlist) {
		if (textures.find(asset.first) != textures.end())
			throw std::logic_error("Two textures cannot have the same name");
		textures.insert({ asset.first, sf::Texture() });
		textures.at(asset.first).loadFromFile(asset.second);
		assetKeys[assetKeys.size() - 1].insert(asset.first);
	}
}

void ResourceManager::unloadState() {
	for (const auto& key : assetKeys[assetKeys.size() - 1]) { // check each key at the top state
		bool exists = ([&]() -> bool { // Check to see if the key exists
			for (int i = 0; i < assetKeys.size() - 1; i++) { // iterate over other pages
				if (assetKeys[i].find(key) != assetKeys[i].end()) // If exists in ANY page, say it exists
					return true;
			}
			return false;
			})();
			if (!exists) // Remove resource if it doesn't exist anywhere else
				textures.erase(key);
	}
}
