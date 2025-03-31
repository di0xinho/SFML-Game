#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"

int main() {
    // Utworzenie okna gry
    sf::RenderWindow window(sf::VideoMode(800, 600), "Platformer Game");
    window.setFramerateLimit(60); // Ograniczenie FPS do 60

    // Utworzenie maszyny stanów
    StateMachine stateMachine;

    // Dodanie stanu menu
    stateMachine.pushState(std::make_unique<MenuState>(stateMachine));

    sf::Clock clock;

    // G³ówna pêtla gry
    while (window.isOpen()) {
        // Obs³uga wejœcia
        stateMachine.handleInput(window);

        // Obliczanie czasu delta
        float deltaTime = clock.restart().asSeconds();

        // Czyszczenie okna
        window.clear();

        // Aktualizacja i renderowanie stanów
        stateMachine.update(deltaTime);
        stateMachine.render(window);

        // Wyœwietlanie okna
        window.display();
    }

    return 0;
}