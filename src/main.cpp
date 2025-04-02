#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"
#include "SoundManager.hpp"
#include <iostream>

int main() {
    // Utworzenie okna gry
    sf::RenderWindow window(sf::VideoMode(800, 600), "Platformer Game");
    window.setFramerateLimit(60); // Ograniczenie FPS do 60

    // Utworzenie SoundManagera
    SoundManager soundManager;
    soundManager.loadMusic("menu", "../../../../Assets/Music/menu-music.ogg");
    soundManager.setMusicLoop("menu", true); // Ustawienie zapêtlenia dla muzyki menu
    soundManager.loadMusic("game", "../../../../Assets/Music/game-music.ogg");
    soundManager.setMusicLoop("game", true); // Ustawienie zapêtlenia dla muzyki w grze

    // Utworzenie maszyny stanów
    StateMachine stateMachine(&soundManager);

    // Dodanie stanu menu
    stateMachine.pushState(std::make_unique<MenuState>(stateMachine, &soundManager));

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