#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "State.hpp"
#include "GameState.hpp"
#include "GameConfig.hpp"
#include "GameData.hpp"

// Klasa reprezentuj¹ca stan zakoñczenia gry (wygrana/przegrana)
class GameOverState : public State {
public:
    // Konstruktor GameOverState.
    // @param data - wskaŸnik na g³ówn¹ strukturê gry
    // @param finalScore - koñcowy wynik gracza (iloœæ zebranych monet)
    // @param won - czy gracz wygra³ (true) czy przegra³ (false)
    GameOverState(std::shared_ptr<GameData> data, int finalScore, bool won);

    // Inicjalizacja stanu, ³adowanie zasobów
    void Init() override;

    // Obs³uga wejœcia u¿ytkownika (np. restart gry)
    void HandleInput() override;

    // Aktualizacja stanu (nieu¿ywana w tym stanie)
    void Update(float dt) override;

    // Rysowanie ekranu koñca gry
    void Draw(float dt) override;

private:
    // --- Dane ogólne ---
    std::shared_ptr<GameData> _data;      // Dane gry, assety, mened¿ery itd.
    int _finalScore;                      // Wynik uzyskany przez gracza
    bool _won;                            // Czy gracz wygra³

    // --- Zasoby ekranu koñca gry ---
    sf::Texture* gameOverTexture = nullptr;   // Tekstura ekranu koñca gry
    sf::Font* font = nullptr;                 // Czcionka do napisów na ekranie
    sf::Sound* gameOverSound = nullptr;       // DŸwiêk koñca gry (wygrana/przegrana)
    sf::Sprite gameOverSprite;                // Sprite wyœwietlany na ekranie koñca gry
};