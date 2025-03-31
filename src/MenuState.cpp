#include "MenuState.hpp"
#include "GameState.hpp"
#include "StateMachine.hpp"

MenuState::MenuState(StateMachine& machine)
    : stateMachine(machine) {
    if (!font.loadFromFile("path/to/font.ttf")) {
        // Obs³uga b³êdu ³adowania czcionki
    }

    title.setFont(font);
    title.setString("Platformer Game");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(200.0f, 150.0f); // Ustawienie pozycji tytu³u

    instructions.setFont(font);
    instructions.setString("Press Enter to Start");
    instructions.setCharacterSize(30);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(220.0f, 300.0f); // Ustawienie pozycji instrukcji
}

void MenuState::handleInput(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        // Zmiana stanu na GameState
        stateMachine.changeState(std::make_unique<GameState>(stateMachine));
    }
}

void MenuState::update(float deltaTime) {
    // Aktualizacja logiki menu (jeœli jest potrzebna)
}

void MenuState::render(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(instructions);
}