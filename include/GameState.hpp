#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "State.hpp"
#include "GameData.hpp"
#include "GameConfig.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include "Player.hpp"
#include "HUD.hpp"
#include "Coin.hpp"
#include "Trophy.hpp"
#include "Enemy.hpp"
#include "Weapon.hpp"
#include "MoveLeftCommand.hpp"
#include "MoveRightCommand.hpp"
#include "JumpCommand.hpp"
#include "AttackCommand.hpp"

// Klasa reprezentuj¹ca g³ówny stan gry
class GameState : public State {
public:
    // Konstruktor przyjmuj¹cy wskaŸnik na g³ówne dane gry
    GameState(std::shared_ptr<GameData> data);

    // Inicjalizacja stanu gry
    void Init() override;

    // Obs³uga wejœcia u¿ytkownika
    void HandleInput() override;

    // Aktualizacja stanu gry (logika gry, animacje itd.)
    void Update(float dt) override;

    // Rysowanie wszystkiego na ekranie
    void Draw(float dt) override;

    // Wznawia grê po pauzie
    void resume() override;

    // Tworzy platformê o zadanym rozmiarze, pozycji i kolorze
    sf::RectangleShape makePlatform(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& color) {
        sf::RectangleShape plat(size);
        plat.setPosition(pos);
        plat.setFillColor(color);
        return plat;
    }

private:
    std::shared_ptr<GameData> _data;     // Dane gry

    // --- Grafika t³a i ziemi ---
    sf::Sprite _background;              // T³o gry
    sf::Sprite _land;                    // Ziemia/platforma bazowa

    // --- Obiekty gry ---
    Player _player;                      // Gracz
    HUD _hud;                            // Wyœwietlacz punktów, ¿yæ itd.
    sf::View _camera;                    // Kamera (widok)
    Trophy trophy;                       // Trofeum (cel gry)

    // --- Elementy poziomu ---
    std::vector<sf::RectangleShape> platforms; // Platformy
    std::vector<Coin> coins;                   // Monety do zebrania
    std::vector<Enemy> enemies;                // Przeciwnicy
    std::vector<Weapon> weapons;               // Bronie (np. rzucone przez gracza)

    // --- Dane pomocnicze do generowania platform ---
    struct PlatformData {
        sf::Vector2f size, pos;
        sf::Color color;
    };

    // --- Zasoby gry ---
    sf::Texture* weaponTexture = nullptr; // Tekstura broni

    // --- Statystyki gry ---
    int score = 0;                        // Wynik gracza
    int lives = 3;                        // Liczba ¿yæ

    // --- Zasoby dŸwiêkowe i czcionki ---
    sf::Font* font = nullptr;             // Czcionka gry
    sf::Music* gameMusic = nullptr;       // Muzyka gry
    sf::Sound* punchSound = nullptr;      // DŸwiêk ataku
};