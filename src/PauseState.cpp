#include "PauseState.hpp"
#include "StateMachine.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

PauseState::PauseState(StateMachine& machine, SoundManager* soundManager)
    : stateMachine(machine), soundManager(soundManager) {
    // Wczytywanie czcionki
    if (!font.loadFromFile("../../../../Assets/Fonts/roboto.ttf")) {
        std::cerr << "Blad: Nie mozna wczytac czcionki!" << std::endl;
    }

    // Ustawianie tekstu
    pauseText.setFont(font);
    pauseText.setString("Pauza");
    pauseText.setCharacterSize(50);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(300, 150);

    instructions.setFont(font);
    instructions.setString("Nacisnij U aby kontynuowac");
    instructions.setCharacterSize(30);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(200, 300);
}


void PauseState::handleInput(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
        soundManager->playMusic("game");
        stateMachine.popState();
    }
}

void PauseState::update(float deltaTime){}

void PauseState::render(sf::RenderWindow& window) {
    window.draw(pauseText);
    window.draw(instructions);
}