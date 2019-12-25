#pragma once
#include <unordered_map>
#include <memory>
#include <map>
#include <string>

template <class AssetType>
class AssetManager
{
public:
	AssetType& getAsset(std::string name) const;
	void addAsset(std::string name, std::shared_ptr<AssetType> asset);
	void cleanAsset(std::string id);
private:
	std::unordered_map<std::string, std::shared_ptr<AssetType>> Assets;
};

#include "AssetManager.tpp"