#include "PauseState.hpp"
#include "StateMachine.hpp"
#include "InputHandler.hpp"
#include "PauseCommand.hpp"

PauseState::PauseState(StateMachine& machine)
    : stateMachine(machine) {
    if (!font.loadFromFile("C:\\Users\\mm-20\\Desktop\\TestingGame2\\Assets\\Fonts\\Roboto.ttf")) {
        // Obs�uga b��du za�adowania czczionki
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
    // U�ywamy InputHandler do obs�ugi klawisza "P"
    static InputHandler inputHandler;
    inputHandler.bindCommand(sf::Keyboard::P, std::make_unique<PauseCommand>(stateMachine));
    inputHandler.handleInput(window);
}

void PauseState::update(float deltaTime) {
    // Aktualizacja logiki pauzy (je�li jest potrzebna)
}

void PauseState::render(sf::RenderWindow& window) {
    window.draw(pauseText);
    window.draw(instructions);
}