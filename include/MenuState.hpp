#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "State.hpp"
#include "GameState.hpp"
#include "GameConfig.hpp"
#include "GameData.hpp"

// Klasa reprezentuj¹ca stan menu g³ównego gry
class MenuState : public State
{
public:
    // Konstruktor przyjmuj¹cy wskaŸnik na dane gry
    MenuState(std::shared_ptr<GameData> data);

    // Inicjalizuje stan menu (³adowanie zasobów)
    void Init() override;

    // Obs³uguje wejœcie u¿ytkownika w menu
    void HandleInput() override;

    // Aktualizuje stan menu (np. animacje t³a, efekty)
    void Update(float dt) override;

    // Rysuje ekran menu
    void Draw(float dt) override;

private:
    std::shared_ptr<GameData> _data;    // Dane gry, assety i mened¿ery

    sf::Font* robotoFont = nullptr;     // Czcionka menu (Roboto)
    sf::Music* menuMusic = nullptr;     // Muzyka w tle menu

    float buttonScale = 0.5f;           // Skala przycisków w menu
    int fontSize = 42;                  // Rozmiar czcionki

    sf::Sprite backgroundSprite;        // T³o menu
    sf::Sprite playButtonSprite;        // Przycisk "Graj"
};