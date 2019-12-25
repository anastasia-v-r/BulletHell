#include "AssetManager.hpp"
#include <stdexcept>

template <class AssetType>
AssetType& AssetManager<AssetType>::getAsset(std::string id) const {
	if (Assets.at(id) == null)
		throw std::invalid_argument("This resource is not loaded");
	
	return Assets[id];
}

template <class AssetType>
void AssetManager<AssetType>::addAsset(std::string id, std::shared_ptr<AssetType> asset) {
	if (Assets.find(id) != Assets.end())
		throw std::invalid_argument("This id is already in use");

	Assets.emplace(std::make_pair(id, asset));
}

template <class AssetType>
void AssetManager<AssetType>::cleanAsset(std::string id) {
	for (auto it = Assets.cend(); it != Assets.cbegin(); it--) {

	}
}