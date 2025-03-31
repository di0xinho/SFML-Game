#include "PauseState.hpp"
#include "StateMachine.hpp"

PauseState::PauseState(StateMachine& machine)
    : stateMachine(machine) {
    if (!font.loadFromFile("C:\\Users\\mm-20\\Desktop\\TestingGame2\\Assets\\Fonts\\Roboto.ttf")) {
        // Obs�uga b��du �adowania czcionki
        throw std::runtime_error("Nie mo�na za�adowa� czcionki");
    }

    pauseText.setFont(font);
    pauseText.setString("Paused");
    pauseText.setCharacterSize(50);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(300.0f, 200.0f); // Ustawienie pozycji tekstu pauzy

    instructions.setFont(font);
    instructions.setString("Press P to Resume");
    instructions.setCharacterSize(30);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(250.0f, 300.0f); // Ustawienie pozycji instrukcji
}

void PauseState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
            // Powr�t do poprzedniego stanu (gry)
            stateMachine.popState();
        }
    }
}

void PauseState::update(float deltaTime) {
    // Aktualizacja logiki pauzy (je�li jest potrzebna)
}

void PauseState::render(sf::RenderWindow& window) {
    window.draw(pauseText);
    window.draw(instructions);
}