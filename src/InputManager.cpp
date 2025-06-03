#include "InputManager.hpp"

// Sprawdza, czy dany klawisz zosta³ wciœniêty (tylko raz do momentu puszczenia)
bool InputManager::isKeyPressed(sf::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}

// Sprawdza, czy dany przycisk myszy zosta³ wciœniêty (tylko raz do momentu puszczenia)
// Uwaga: SFML nie rozró¿nia "pressed" i "down" bezpoœrednio, wiêc musisz obs³u¿yæ ten stan w logice gry lub przez eventy
bool InputManager::isMouseButtonPressed(sf::Mouse::Button button)
{
    return sf::Mouse::isButtonPressed(button);
}

// Zwraca pozycjê kursora myszy wzglêdem okna gry
sf::Vector2i InputManager::getMousePosition(sf::RenderWindow& window)
{
    return sf::Mouse::getPosition(window);
}

// Sprawdza, czy dany prostok¹t zosta³ klikniêty wybranym przyciskiem myszy
bool InputManager::isRectClicked(const sf::FloatRect& rect, sf::Mouse::Button button, sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(button))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (rect.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            return true;
        }
    }
    return false;
}