#include "UIManager.hpp"
#include <stdexcept>
#include <string>
#include "UIElement.hpp"

void UIManager::addElement(std::pair<std::string, UIElement> newElement) {
	m_Elements.insert(newElement);
}

void UIManager::removeElement(const std::string& id) {
	if (m_Elements.find(id) == m_Elements.end())
		throw std::invalid_argument("This element does not exist");
	m_Elements.erase(id);
}

void UIManager::draw(sf::RenderTarget& window, sf::RenderStates states) const {
	for (const auto& element : m_Elements) {
		window.draw(element.second);
	}
}
