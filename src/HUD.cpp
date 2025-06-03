#include "HUD.hpp"

// Konstruktor domyœlny HUD-u
HUD::HUD() {}

// Inicjalizuje HUD, ustawia font i podstawowe parametry tekstów
void HUD::Init(sf::Font* font) {
    _font = font;

    _scoreText.setFont(*_font);
    _scoreText.setCharacterSize(32);
    _scoreText.setFillColor(sf::Color::White);

    _livesText.setFont(*_font);
    _livesText.setCharacterSize(32);
    _livesText.setFillColor(sf::Color::White);

    UpdateText();
}

// Ustawia wynik i aktualizuje tekst
void HUD::SetScore(int score) {
    _score = score;
    UpdateText();
}

// Ustawia liczbê ¿yæ i aktualizuje tekst
void HUD::SetLives(int lives) {
    _lives = lives;
    UpdateText();
}

// Aktualizuje zawartoœæ tekstów wyœwietlanych na HUDzie
void HUD::UpdateText() {
    _scoreText.setString("Wynik: " + std::to_string(_score));
    _livesText.setString("Zdrowie: " + std::to_string(_lives));
}

// Rysuje HUD na ekranie, prawy górny róg, zawsze w domyœlnym widoku
void HUD::Draw(sf::RenderWindow& window) {
    // Ustaw widok na domyœlny (wa¿ne!)
    window.setView(window.getDefaultView());

    // Rozmiar okna do dynamicznego pozycjonowania
    auto winSize = window.getSize();

    // Pozycjonowanie: prawy górny róg (odstêp 20px)
    float margin = 20.f;
    sf::FloatRect livesBounds = _livesText.getLocalBounds();
    sf::FloatRect scoreBounds = _scoreText.getLocalBounds();

    _livesText.setPosition(winSize.x - livesBounds.width - margin, margin);
    _scoreText.setPosition(winSize.x - scoreBounds.width - margin, margin + livesBounds.height + 10.f);

    window.draw(_livesText);
    window.draw(_scoreText);
}