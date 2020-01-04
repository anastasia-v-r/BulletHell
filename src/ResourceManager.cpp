#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <stdexcept>

ResourceManager& ResourceManager::instance() {
	static ResourceManager s_instance;
	return s_instance;
}

ResourceManager::ResourceManager() {
	game_font.loadFromFile("assets/Global/font/OpenSans-Regular.ttf");
	textures.insert({ "GameSplash", sf::Texture() });
	textures.at("1").loadFromFile("assets/splashScreen/BulletHellSplash.png");
	textures.insert({ "StudioSplash", sf::Texture() });
	textures.at("2").loadFromFile("assets/splashScreen/ValorianSplash.png");
	
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

}
