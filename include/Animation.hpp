#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

// Klasa odpowiadaj¹ca za animacjê 2D (przechowywanie klatek i logikê prze³¹czania miêdzy nimi)
class Animation {
public:
    // Konstruktory
    Animation();
    Animation(const std::vector<const sf::Texture*>& frames, float frameTime);

    // Ustawia nowe klatki i czas trwania jednej klatki animacji
    void SetFrames(const std::vector<const sf::Texture*>& frames, float frameTime);

    // Aktualizuje animacjê na podstawie up³ywu czasu (dt)
    void Update(float dt);

    // Resetuje animacjê do pierwszej klatki
    void Reset();

    // Zwraca wskaŸnik do aktualnej tekstury (klatki animacji)
    const sf::Texture* GetCurrentFrame() const;

    // Zwraca indeks aktualnej klatki animacji
    std::size_t GetCurrentFrameIndex() const;

private:
    std::vector<const sf::Texture*> _frames; // Wektor klatek animacji
    float _frameTime = 0.1f;                 // Czas trwania jednej klatki (w sekundach)
    float _timer = 0.f;                      // Licznik czasu do zmiany klatki
    std::size_t _currentFrame = 0;           // Indeks aktualnej klatki
};