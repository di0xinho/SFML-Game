#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"

int main() {
    // Utworzenie okna gry
    sf::RenderWindow window(sf::VideoMode(800, 600), "Platformer Game");
    window.setFramerateLimit(60); // Ograniczenie FPS do 60

    // Utworzenie maszyny stan�w
    StateMachine stateMachine;

    // Dodanie stanu menu
    stateMachine.pushState(std::make_unique<MenuState>(stateMachine));

    sf::Clock clock;

    // G��wna p�tla gry
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

        // Obs�uga wej�cia, aktualizacja i renderowanie stan�w
        stateMachine.handleInput(window);
        stateMachine.update(deltaTime);
        stateMachine.render(window);

        // Wy�wietlanie okna
        window.display();
    }

    return 0;
}