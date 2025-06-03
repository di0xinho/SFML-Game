#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Animation.hpp"

// Klasa reprezentuj¹ca monetê do zebrania przez gracza (do naliczania punktów)
class Coin {
public:
    // Konstruktor inicjuj¹cy monetê na danej pozycji z przekazanymi klatkami animacji
    Coin(const sf::Vector2f& pos, const std::vector<const sf::Texture*>& sharedFrames);

    // Aktualizuje stan animacji monety
    void Update(float dt);

    // Rysuje monetê na ekranie
    void Draw(sf::RenderWindow& window) const;

    // Ustawia pozycjê monety
    void SetPosition(const sf::Vector2f& pos);

    // Pobiera pozycjê monety
    sf::Vector2f GetPosition() const;

    // Pobiera prostok¹t kolizyjny monety
    sf::FloatRect GetCollisionRect() const;

    // Sprawdza, czy moneta zosta³a zebrana
    bool IsCollected() const;

    // Zaznacza, ¿e moneta zosta³a zebrana
    void Collect();

    // Ustawia dŸwiêk odtwarzany po zebraniu monety
    void setCollectedCoinSound(sf::Sound* sound);

private:
    sf::Vector2f position;           // Pozycja monety na mapie
    sf::Vector2f size;               // Rozmiar monety (ustalany na podstawie klatki animacji)
    bool collected = false;          // Czy moneta zosta³a ju¿ zebrana?
    Animation anim;                  // Animacja monety
    sf::Sound* collectCoinSound = nullptr; // DŸwiêk odtwarzany przy zebraniu monety
};