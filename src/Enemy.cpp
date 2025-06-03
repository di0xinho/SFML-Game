#include "Enemy.hpp"

// Konstruktor przeciwnika: ustawia pozycjê, animacjê, domyœlne parametry ruchu i stanu
Enemy::Enemy(const sf::Vector2f& startPos, const std::vector<const sf::Texture*>& sharedTextures)
    : position(startPos),
    size(32.f, 32.f),
    patrolDistance(100.f),
    walked(0.f),
    direction(1),
    speed(40.f),
    anim(sharedTextures, 0.2f),
    alive(true) {
}

// Aktualizuje stan przeciwnika: animacja, ruch, patrol, grawitacja i kolizja z pod³o¿em
void Enemy::Update(float dt, float groundY)
{
    anim.Update(dt);

    // Obs³uga efektu trafienia (przeciwnik miga na czerwono)
    if (hitTimer > 0.0f) {
        hitTimer -= dt;
        if (hitTimer < 0.0f) hitTimer = 0.0f;
    }

    // Grawitacja + kolizja z pod³o¿em
    velocity.y += gravity * dt;
    float newY = position.y + velocity.y * dt;

    isOnGround = false;

    // Detekcja kontaktu z pod³o¿em (przejœcie dolnej krawêdzi przez groundY)
    if (
        position.x + size.x > 0 && position.x < 10000.f && // wróg jest w "grze" (przyk³adowa szerokoœæ mapy)
        groundY >= position.y + size.y && groundY <= newY + size.y // dolna krawêdŸ przechodzi przez groundY
        ) {
        newY = groundY - size.y;
        velocity.y = 0;
        isOnGround = true;
    }

    position.y = newY;

    // Patrolowanie przestrzeni tylko bêd¹c na ziemi
    if (isOnGround) {
        float step = speed * dt * direction;
        position.x += step;
        walked += std::abs(step);

        if (walked >= patrolDistance) {
            direction *= -1; // zmieñ kierunek
            walked = 0;
        }
    }
}

// Rysuje przeciwnika z odpowiednim kolorem (czerwony jeœli trafiony - efekt migania)
void Enemy::Draw(sf::RenderWindow& window) const
{
    const sf::Texture* frame = anim.GetCurrentFrame();
    if (frame && alive) {
        sf::Sprite sprite;
        sprite.setTexture(*frame);
        sprite.setPosition(position);
        sprite.setScale(size.x / frame->getSize().x, size.y / frame->getSize().y);
        if (hitTimer > 0.0f) {
            sprite.setColor(sf::Color::Red);
        }
        else {
            sprite.setColor(sf::Color::White);
        }
        window.draw(sprite);
    }
}

// Ustawia pozycjê przeciwnika
void Enemy::SetPosition(const sf::Vector2f& pos) { position = pos; }

// Zwraca pozycjê przeciwnika
sf::Vector2f Enemy::GetPosition() const { return position; }

// Zwraca prostok¹t kolizyjny przeciwnika
sf::FloatRect Enemy::GetCollisionRect() const { return sf::FloatRect(position, size); }

// Trafienie wroga: dŸwiêk, efekt, zmniejszenie hp i ewentualnie jego zabicie
void Enemy::Hit()
{
    if (!alive) return;

    health--;
    if (ouchSound) {
        ouchSound->play();
    }
    hitTimer = hitDuration; // wróg bêdzie czerwony przez jakiœ czas (hitDuration)
    if (health <= 0) {
        Kill();
    }
}

// Ustawia alive na false (wróg jest martwy)
void Enemy::Kill() { alive = false; }

// Zwraca, czy wróg ¿yje
bool Enemy::IsAlive() const { return alive; }

// Ustawia wskaŸnik na dŸwiêk trafienia (efekt "ouch")
void Enemy::setHitSound(sf::Sound* sound) {
    ouchSound = sound;
}