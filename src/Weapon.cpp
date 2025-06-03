#include "Weapon.hpp"

// Konstruktor: ustawia pozycjê, prêdkoœæ, czas ¿ycia, teksturê i domyœlne parametry pocisku
Weapon::Weapon(const sf::Vector2f& startPos, float moveSpeed, float lifeTime, const sf::Texture* texture)
    : position(startPos),
    speed(moveSpeed),
    rotation(0.f),
    timer(0.f),
    maxLifetime(lifeTime),
    alive(true),
    size(16.f),
    texture(texture) {
}

// Aktualizuje pozycjê, obrót i czas ¿ycia pocisku
bool Weapon::Update(float dt, const std::vector<Enemy>& enemies)
{
    if (!alive) return false;

    // Ruch w prawo
    position.x += speed * dt;

    // Obrót (1 stopieñ na klatkê)
    rotation += 1.0f;
    if (rotation >= 360.0f) rotation -= 360.0f;

    // Timer ¿ycia pocisku
    timer += dt;
    if (timer > maxLifetime) alive = false;

    return alive;
}

// Rysuje pocisk (sprite lub czerwony kwadrat, jeœli brak tekstury)
void Weapon::Draw(sf::RenderWindow& window) const
{
    if (!alive) return;

    // Ustawienie sprite'a
    sf::Sprite sprite;
    if (texture) {
        sprite.setTexture(*texture);
        sprite.setPosition(position);
        sprite.setOrigin(size / 2.f, size / 2.f);
        sprite.setRotation(rotation);
        sprite.setScale(
            size / texture->getSize().x,
            size / texture->getSize().y
        );
        window.draw(sprite);
    }
    else {
        // Jeœli nie ma tekstury, rysujemy czerwony kwadrat
        sf::RectangleShape shape(sf::Vector2f(size, size));
        shape.setOrigin(size / 2.f, size / 2.f);
        shape.setPosition(position);
        shape.setRotation(rotation);
        shape.setFillColor(sf::Color::Red);
        window.draw(shape);
    }
}

// Sprawdza kolizjê pocisku z wrogiem
bool Weapon::CollidesWith(const Enemy& enemy) const
{
    sf::FloatRect weaponRect(position.x - size / 2.f, position.y - size / 2.f, size, size);
    return weaponRect.intersects(enemy.GetCollisionRect());
}