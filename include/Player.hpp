#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>
#include "Weapon.hpp"
#include <memory>
#include "GameData.hpp"
#include "Animation.hpp"
#include "Command.hpp"

// Klasa reprezentuj¹ca gracza
class Player {
public:
    Player();

    // Inicjalizuje gracza na podstawie g³ównych danych gry (assetów)
    void Init(std::shared_ptr<GameData> data);

    // Obs³uga wejœcia: przyjmuje mapê aktualnych stanów klawiszy
    void handleInput(const std::unordered_map<sf::Keyboard::Key, bool>& keystates);

    // Aktualizuje stan gracza, ruch, animacjê, kolizje z platformami
    void Update(float dt, float groundY, const std::vector<sf::RectangleShape>& platforms);

    // Rysuje gracza na ekranie
    void Draw(sf::RenderWindow& window) const;

    // Ruch gracza (manualnie lub przez komendy)
    void MoveLeft();
    void MoveRight();
    void Jump();

    // Ustawia pozycjê startow¹ gracza
    void SetStartPosition(const sf::Vector2f& startPos);

    // Pobiera prostok¹t kolizyjny gracza
    sf::FloatRect GetCollisionRect() const;

    // Pobiera aktualn¹ pozycjê gracza
    sf::Vector2f GetPosition() const;

    // Pobiera rozmiar sprite'a animacji
    sf::Vector2u GetSpriteSize() const;

    // Pobiera wysokoœæ gracza
    float GetHeight() const;

    // Rozpoczyna efekt migania na okreœlony czas (np. po trafieniu)
    void startBlink(float duration);

    // Czy gracz aktualnie miga?
    bool isBlinking() const;

    // Przesuwa gracza o zadany offset
    void moveBy(const sf::Vector2f& offset);

    // Ogranicza pozycjê gracza do przedzia³u minX-maxX
    void constrainToBounds(float minX, float maxX);

    // Czy gracz mo¿e rzuciæ broni¹ (czy cooldown siê skoñczy³)
    bool canShoot() const;

    // Resetuje cooldown rzutu broni¹
    void resetWeaponCooldown();

    // Zwraca wskaŸnik do dŸwiêku rzutu no¿em
    sf::Sound* getKnifeThrowSound() const;

    // Próbuje rzuciæ broni¹ i dodaje j¹ do listy broni
    void tryThrowWeapon(sf::Texture* weaponTexture, std::vector<Weapon>& weaponList);

    // Ustawia dŸwiêk skoku
    void setJumpSound(sf::Sound* sound);

    // Ustawia dŸwiêk rzutu no¿em
    void setKnifeThrowSound(sf::Sound* sound);

    // Przypisuje komendê (wzorzec Command) do klawisza
    void bindCommand(sf::Keyboard::Key key, std::unique_ptr<Command> command);

    // Mapa powi¹zañ klawiszy z komendami
    std::unordered_map<sf::Keyboard::Key, std::unique_ptr<Command>> commandMap;

private:
    std::shared_ptr<GameData> _data;   // WskaŸnik do danych gry

    sf::Vector2f _position;            // Pozycja gracza
    sf::Vector2f _velocity;            // Prêdkoœæ gracza
    bool _onGround;                    // Czy gracz stoi na ziemi

    // Animacje i wskaŸnik do aktualnej animacji
    Animation _idleAnim;
    Animation _runAnim;
    Animation _jumpAnim;
    Animation* _currentAnim;

    float _moveSpeed;                  // Prêdkoœæ ruchu
    float _jumpImpulse;                // Si³a skoku
    float _gravity;                    // Grawitacja

    float weaponCooldown = 0.0f;       // Czas do koñca cooldownu rzutu broni¹
    const float weaponCooldownDuration = 0.5f; // D³ugoœæ cooldownu rzutu broni¹

    bool blinking = false;             // Czy trwa efekt migania po trafieniu
    float blinkTimer = 0.0f;           // Timer migania
    float blinkDuration = 1.0f;        // D³ugoœæ trwania migania

    sf::Sound* knifeThrowSound = nullptr;  // DŸwiêk rzutu no¿em
    sf::Sound* jumpSound = nullptr;        // DŸwiêk skoku
};