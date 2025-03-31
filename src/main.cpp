#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "GameState.hpp"

int main() {
    // Utworzenie okna gry
    sf::RenderWindow window(sf::VideoMode(800, 600), "Platformer Game");
    window.setFramerateLimit(60); // Ograniczenie FPS do 60

    // Utworzenie maszyny stanów i dodanie stanu gry
    StateMachine stateMachine;
    stateMachine.pushState(std::make_unique<GameState>());

    sf::Clock clock;

    // G³ówna pêtla gry
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Obliczanie czasu delta
        float deltaTime = clock.restart().asSeconds();

        // Czyszczenie okna
        window.clear();

        // Obs³uga wejœcia, aktualizacja i renderowanie stanów
        stateMachine.handleInput(window);
        stateMachine.update(deltaTime);
        stateMachine.render(window);

        // Wyœwietlanie okna
        window.display();
    }

    return 0;
}