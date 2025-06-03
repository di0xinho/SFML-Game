#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Klasa zarz¹dzaj¹ca wejœciem u¿ytkownika (klawiatura, mysz)
class InputManager {
public:
    InputManager() {}
    ~InputManager() {}

    // Sprawdza, czy dany klawisz zosta³ wciœniêty (tylko raz do momentu puszczenia)
    bool isKeyPressed(sf::Keyboard::Key key);

    // Sprawdza, czy przycisk myszy zosta³ wciœniêty (tylko raz do momentu puszczenia)
    bool isMouseButtonPressed(sf::Mouse::Button button);

    // Zwraca pozycjê kursora myszy wzglêdem okna gry
    sf::Vector2i getMousePosition(sf::RenderWindow& window);

    // Sprawdza, czy dany prostok¹t (np. przycisk) zosta³ klikniêty wybranym przyciskiem myszy
    bool isRectClicked(const sf::FloatRect& rect, sf::Mouse::Button button, sf::RenderWindow& window);
};