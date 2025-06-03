#include "Trophy.hpp"

// Domyœlny konstruktor 
Trophy::Trophy(): basePosition{ 0.f, 0.f }, position{ 0.f, 0.f }, size{ 0.f, 0.f }, texture(nullptr), floatTimer(0.0f){}

// Konstruktor z parametrami - ustawia pozycjê bazow¹, aktualn¹ i teksturê
Trophy::Trophy(const sf::Vector2f& pos, const sf::Texture* texture)
    : basePosition(pos), position(pos), texture(texture), floatTimer(0.0f)
{
    // Ustal rozmiar na podstawie rozmiaru tekstury
    if (texture)
        size = sf::Vector2f(texture->getSize());
    else
        size = sf::Vector2f(0.f, 0.f);
}

// Aktualizuje efekt unoszenia trofeum (oscylacja góra/dó³)
void Trophy::Update(float dt)
{
    floatTimer += dt * floatSpeed; // Zwiêksz licznik czasu
    // Efekt unoszenia: pozycja.y oscyluje sinusoidalnie wzglêdem pozycji bazowej
    position.y = basePosition.y + std::sin(floatTimer) * floatAmplitude;
}

// Rysuje trofeum na ekranie w aktualnej pozycji
void Trophy::Draw(sf::RenderWindow& window) const
{
    if (!texture) return;
    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setPosition(position);
    window.draw(sprite);
}

// Zwraca prostok¹t kolizji trofeum
sf::FloatRect Trophy::GetCollisionRect() const
{
    return sf::FloatRect(position, size);
}