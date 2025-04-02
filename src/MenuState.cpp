#include "MenuState.hpp"
#include "GameState.hpp"
#include "StateMachine.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

MenuState::MenuState(StateMachine& machine, SoundManager* soundManager)
    : stateMachine(machine), soundManager(soundManager) {
    // Inicjalizacja muzyki menu
    soundManager->playMusic("menu");

    // Wczytywanie czcionki
    if (!font.loadFromFile("../../../../Assets/Fonts/roboto.ttf")) {
        std::cerr << "Blad: Nie mozna wczytac czcionki!" << std::endl;
    }
    else {
        std::cout << "Czcionka wczytana poprawnie." << std::endl;
    }

    title.setFont(font);
    title.setString("Platformer Game");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(200.0f, 100.0f);

    instructions.setFont(font);
    instructions.setString("Press Enter to Start");
    instructions.setCharacterSize(30);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(220.0f, 300.0f);
}

void MenuState::handleInput(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        stateMachine.changeState(std::make_unique<GameState>(stateMachine, soundManager));
    }
}

void MenuState::update(float deltaTime) {
    // Aktualizacja logiki menu
}

void MenuState::render(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(instructions);
}