#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "UIElement.hpp"

class UIManager : public sf::Drawable
{
public:
	void addElement(std::pair<std::string, UIElement*> newElement);
	void removeElement(const std::string& id);
	UIElement& getElement(const std::string& id);
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
private:
	std::map<std::string, UIElement*> m_Elements;
};