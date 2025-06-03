#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.hpp"

// Klasa reprezentuj¹ca pocisk (lataj¹cy nó¿/miecz) wystrzeliwany przez gracza
class Weapon
{
public:
    // Konstruktor
    // @param startPos - Pocz¹tkowa pozycja broni
    // @param moveSpeed - Prêdkoœæ poruszania siê broni (pocisku)
    // @param lifeTime - Maksymalny czas ¿ycia pocisku (w sekundach)
    // @param texture - WskaŸnik do tekstury pocisku
    Weapon(const sf::Vector2f& startPos, float moveSpeed, float lifeTime, const sf::Texture* texture);

    // Aktualizuje stan broni i sprawdza kolizje z wrogami (zwraca true jeœli trafi³)
    bool Update(float dt, const std::vector<Enemy>& enemies);

    // Rysuje pocisk/broñ na ekranie
    void Draw(sf::RenderWindow& window) const;

    // Sprawdza, czy pocisk nadal ¿yje (nie wygas³ i nie zderzy³ siê)
    bool IsAlive() const { return alive; }

    // Sprawdza kolizjê pocisku z danym wrogiem
    bool CollidesWith(const Enemy& enemy) const;

    // Zwraca aktualn¹ pozycjê pocisku
    sf::Vector2f GetPosition() const { return position; }

    // Zwraca aktualn¹ rotacjê pocisku
    float GetRotation() const { return rotation; }

    // Uœmierca pocisk/broñ (po kolizji)
    void Kill() { alive = false; }

private:
    sf::Vector2f position;         // Aktualna pozycja pocisku
    float speed;                   // Prêdkoœæ poruszania siê pocisku
    float rotation = 0.f;          // K¹t obrotu pocisku
    float timer = 0.f;             // Licznik czasu ¿ycia pocisku
    float maxLifetime = 1.f;       // Maksymalny czas ¿ycia pocisku
    bool alive = true;             // Czy pocisk jest aktywny
    float size = 32.f;             // Rozmiar pocisku (mo¿na ustawiæ wg tekstury)
    const sf::Texture* texture;    // WskaŸnik do tekstury pocisku
};