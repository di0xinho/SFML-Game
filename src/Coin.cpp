#include "Coin.hpp"

// Konstruktor: ustawia pozycjê, rozmiar na podstawie pierwszej klatki animacji, stan zebranej oraz animacjê
Coin::Coin(const sf::Vector2f& pos, const std::vector<const sf::Texture*>& sharedFrames)
    : position(pos), collected(false), anim(sharedFrames, 0.07f)
{
    // Ustal rozmiar na podstawie pierwszej klatki animacji
    if (!sharedFrames.empty())
        size = sf::Vector2f(sharedFrames[0]->getSize());
    else
        size = sf::Vector2f(50.f, 50.f); // domyœlny rozmiar
}

// Aktualizuje animacjê monety, jeœli nie zosta³a zebrana
void Coin::Update(float dt) {
    if (!collected)
        anim.Update(dt);
}

// Rysuje monetê na ekranie, jeœli nie zosta³a zebrana
void Coin::Draw(sf::RenderWindow& window) const {
    if (collected) return;
    const sf::Texture* frame = anim.GetCurrentFrame();
    if (frame) {
        sf::Sprite sprite;
        sprite.setTexture(*frame);
        sprite.setPosition(position);
        // Skalowanie do size (opcjonalne – jeœli klatki maj¹ ró¿ny rozmiar)
        sprite.setScale(
            size.x / frame->getSize().x,
            size.y / frame->getSize().y
        );
        window.draw(sprite);
    }
}

// Ustawia wskaŸnik do dŸwiêku zbierania monety
void Coin::setCollectedCoinSound(sf::Sound* sound) {
    collectCoinSound = sound;
}

// Ustawia now¹ pozycjê monety
void Coin::SetPosition(const sf::Vector2f& pos) { position = pos; }

// Zwraca pozycjê monety
sf::Vector2f Coin::GetPosition() const { return position; }

// Zwraca prostok¹t kolizyjny monety
sf::FloatRect Coin::GetCollisionRect() const { return sf::FloatRect(position, size); }

// Sprawdza, czy moneta zosta³a zebrana
bool Coin::IsCollected() const {
    return collected;
}

// Oznacza monetê jako zebran¹ i odtwarza dŸwiêk zbierania, jeœli ustawiony
void Coin::Collect() {
    if (collectCoinSound) {
        collectCoinSound->play();
    }
    collected = true;
}