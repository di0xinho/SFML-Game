#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include "Animation.hpp" 

// Klasa reprezentuj¹ca przeciwnika w grze
class Enemy {
public:
    // Konstruktor przeciwnika
    // @param startPos - pocz¹tkowa pozycja przeciwnika
    // @param sharedTextures - wektor wskaŸników do tekstur animacji
    Enemy(const sf::Vector2f& startPos, const std::vector<const sf::Texture*>& sharedTextures);

    // Aktualizuje stan przeciwnika (ruch, animacje, kolizje, stany)
    void Update(float dt, float groundY);

    // Rysuje przeciwnika na ekranie
    void Draw(sf::RenderWindow& window) const;

    // Ustawia pozycjê przeciwnika
    void SetPosition(const sf::Vector2f& pos);

    // Pobiera pozycjê przeciwnika
    sf::Vector2f GetPosition() const;

    // Pobiera prostok¹t kolizyjny przeciwnika
    sf::FloatRect GetCollisionRect() const;

    // Oznacza trafienie przeciwnika (zmniejsza zdrowie)
    void Hit();

    // Zabija przeciwnika (ustawia alive=false)
    void Kill();

    // Sprawdza, czy przeciwnik ¿yje
    bool IsAlive() const;

    // Ustawia dŸwiêk odtwarzany po trafieniu
    void setHitSound(sf::Sound* sound);

private:
    // --- Pozycja, rozmiar i fizyka ---
    sf::Vector2f position;           // Pozycja przeciwnika
    sf::Vector2f size;               // Rozmiar przeciwnika (na podstawie klatki animacji)
    sf::Vector2f velocity{ 0, 0 };   // Prêdkoœæ przeciwnika (x,y)
    float gravity = 700.0f;          // Si³a grawitacji
    bool isOnGround = false;         // Czy przeciwnik stoi na ziemi?

    // --- Logika ruchu i patrolowania ---
    float patrolDistance = 200.0f;   // Dystans patrolowania
    float walked = 0.0f;             // Przebyty dystans w patrolu
    int direction = 1;               // Kierunek ruchu: -1 (lewo) lub 1 (prawo)
    float speed = 100.0f;            // Prêdkoœæ poruszania siê

    // --- Stan zdrowia i trafienia ---
    int health = 3;                  // Liczba punktów ¿ycia (domyœlnie 3)
    float hitTimer = 0.0f;           // Licznik czasu od trafienia
    float hitDuration = 0.2f;        // Czas trwania efektu trafienia (np. miganie)
    bool alive = true;               // Czy przeciwnik ¿yje?

    // --- Animacja i dŸwiêki ---
    Animation anim;                  // Animacja przeciwnika
    sf::Sound* ouchSound = nullptr;  // DŸwiêk po trafieniu
};