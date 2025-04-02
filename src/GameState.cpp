#include "GameState.hpp"
#include "PauseState.hpp"
#include "StateMachine.hpp"
#include "ScoreManager.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

const float GRAVITY = 500.0f;

GameState::GameState(StateMachine& machine)
    : stateMachine(machine), velocityY(0.0f), isJumping(false), scoreManager() {
    player.setSize(sf::Vector2f(50.0f, 50.0f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(375.0f, 500.0f);

    // Inicjalizacja mapowania klawiszy do komend w InputHandler
    inputHandler.initializeBindings(player, velocityY, isJumping, stateMachine);

    // £adowanie czcionki
    sf::Font font;

    if (!font.loadFromFile("../../../../Assets/Fonts/Roboto.ttf")) {
        // Obs³uga b³êdu za³adowania czczionki
        throw std::runtime_error("Nie mo¿na za³adowaæ czcionki");
    }

    scoreManager.setFont(font);
    scoreManager.setPosition(10.0f, 10.0f);
}

void GameState::handleInput(sf::RenderWindow& window) {
    inputHandler.handleInput(window);

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void GameState::update(float deltaTime) {
    // Grawitacja
    velocityY += GRAVITY * deltaTime;
    player.move(0.0f, velocityY * deltaTime);

    // Sprawdzenie kolizji z pod³o¿em
    if (player.getPosition().y + player.getSize().y >= 550.0f) {
        player.setPosition(player.getPosition().x, 550.0f - player.getSize().y);
        velocityY = 0.0f;
        isJumping = false;
    }

    // Aktualizacja punktacji
    // scoreManager.addPoints(10); // Przyk³adowe dodanie punktów
}

void GameState::render(sf::RenderWindow& window) {
    window.draw(player);
    scoreManager.render(window);
}