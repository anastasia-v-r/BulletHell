#pragma once
#include <SFML/Graphics.hpp>
#include <variant>
#include "UIManager.hpp"

class UIManager;

class UIElement : public sf::Drawable
{
public:
	UIElement(UIManager* parent);
	UIElement(UIElement* parent);
	std::variant<UIElement*, UIManager*>& getParent();
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
private:
	std::variant<UIElement*, UIManager*>  parent;
};