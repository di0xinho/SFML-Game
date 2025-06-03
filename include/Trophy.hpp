#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

// Klasa reprezentuj¹ca trofeum unosz¹ce siê do zebrania przez gracza, w celu ukoñczenia gry
class Trophy {
public:
    // Konstruktor z parametrami (pozycja, wskaŸnik do tekstury)
    Trophy(const sf::Vector2f& pos, const sf::Texture* texture);

    // Domyœlny konstruktor 
    Trophy();

    // Aktualizuje efekt unoszenia siê trofeum (animacja góra/dó³)
    void Update(float dt);

    // Rysuje trofeum na ekranie
    void Draw(sf::RenderWindow& window) const;

    // Zwraca prostok¹t kolizji (do sprawdzania zbierania przez gracza)
    sf::FloatRect GetCollisionRect() const;

private:
    // Pozycja bazowa (np. na pod³odze, punkt odniesienia animacji)
    sf::Vector2f basePosition;

    // Aktualna pozycja (z uwzglêdnieniem efektu unoszenia)
    sf::Vector2f position;

    // Rozmiar trofeum
    sf::Vector2f size;

    // WskaŸnik do tekstury trofeum
    const sf::Texture* texture = nullptr;

    // Licznik czasu dla animacji unoszenia
    float floatTimer = 0.0f;

    // Amplituda unoszenia (jak wysoko siê unosi, w pikselach)
    float floatAmplitude = 14.0f;

    // Prêdkoœæ animacji unoszenia (im wiêcej, tym szybciej)
    float floatSpeed = 2.0f;
};