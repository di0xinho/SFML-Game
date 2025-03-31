#include "MenuState.hpp"
#include "GameState.hpp"
#include "StateMachine.hpp"
#include <filesystem>
#include <iostream>

MenuState::MenuState(StateMachine& machine) : stateMachine(machine) {
    if (!font.loadFromFile("../../../../Assets/Fonts/Roboto.ttf")) {
        // Obs³uga b³êdu za³adowania czczionki
        std::cout << "Aktualny katalog roboczy: " << std::filesystem::current_path() << std::endl;
        throw std::runtime_error("Nie mo¿na za³adowaæ czcionki");
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