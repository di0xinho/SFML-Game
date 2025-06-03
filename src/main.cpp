#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "GameData.hpp"
#include "GameConfig.hpp"
#include "MenuState.hpp"

int main()
{
    // Inicjalizacja okna SFML
    auto window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE, sf::Style::Close);

    window->setFramerateLimit(60);

    // Inicjalizacja urz¹dzenia audio SFML (brak osobnej funkcji jak w Raylib, SFML robi to automatycznie)

    // Tworzenie instancji GameData
    std::shared_ptr<GameData> gameData = std::make_shared<GameData>();
    gameData->window = window;
    gameData->inputManager = std::make_shared<InputManager>();
    gameData->assetManager = std::make_shared<AssetManager>();
    gameData->soundManager = std::make_shared<SoundManager>();

    // Dodanie pocz¹tkowego stanu (MenuState)
    gameData->machine.AddState(std::make_unique<MenuState>(gameData), true);

    // G³ówna pêtla gry
    sf::Clock clock;
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        // Przetwarzanie zmian stanów
        gameData->machine.ProcessStateChanges();

        // Sprawdzanie i obs³uga aktywnego stanu
        if (gameData->machine.GetActiveState())
        {
            float dt = clock.restart().asSeconds();
            auto& activeState = gameData->machine.GetActiveState();
            activeState->HandleInput();
            activeState->Update(dt);

            window->clear(sf::Color::White); // <-- tylko tutaj czyœæ!
            activeState->Draw(dt);           // <-- tylko rysuj!
            window->display();               // <-- tylko tutaj wywo³uj display!
        }
    }

    // Zwalnianie zasobów
    gameData->machine.Clear();
    gameData->assetManager.reset();
    gameData->inputManager.reset();
    gameData->soundManager.reset();
    gameData->window.reset();

    // SFML nie wymaga jawnego zamykania audio

    return 0;
}