#pragma once
#include <SFML/Graphics.hpp>

// Klasa odpowiadaj¹ca za wyœwietlanie HUD (wynik, liczba ¿yæ) na ekranie
class HUD {
public:
    HUD();

    // Inicjalizuje HUD z podan¹ czcionk¹
    void Init(sf::Font* font);

    // Ustawia aktualny wynik
    void SetScore(int score);

    // Ustawia aktualn¹ liczbê ¿yæ
    void SetLives(int lives);

    // Rysuje HUD na ekranie (zawsze wzglêdem okna, NIE kamery)
    void Draw(sf::RenderWindow& window);

private:
    int _score = 0;           // Aktualny wynik gracza
    int _lives = 0;           // Aktualna liczba ¿yæ gracza
    sf::Text _scoreText;      // Tekst wyœwietlaj¹cy wynik
    sf::Text _livesText;      // Tekst wyœwietlaj¹cy liczbê ¿yæ
    sf::Font* _font = nullptr;// Czcionka u¿ywana w HUDzie

    // Aktualizuje teksty HUD po zmianie wyniku lub liczby ¿yæ
    void UpdateText();
};