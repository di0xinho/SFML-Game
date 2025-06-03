#include "Player.hpp"

// Konstruktor: ustawia domyœlne wartoœci gracza
Player::Player(): _onGround(true),_currentAnim(nullptr),_moveSpeed(200.f),_jumpImpulse(-350.f), _gravity(900.f) {}

// Inicjalizacja gracza: ³adowanie animacji, resetowanie prêdkoœci, ustawienie wskaŸnika na dane gry
void Player::Init(std::shared_ptr<GameData> data) {
    _data = data;
    _velocity = sf::Vector2f(0.f, 0.f);
    _onGround = true;

    // £adujemy animacje gracza
    std::vector<const sf::Texture*> idleFrames = { &_data->assetManager->getTexture("player_idle") };
    std::vector<const sf::Texture*> runFrames = {
        &_data->assetManager->getTexture("player_run_1"),
        &_data->assetManager->getTexture("player_run_2"),
        &_data->assetManager->getTexture("player_run_3")
    };
    std::vector<const sf::Texture*> jumpFrames = { &_data->assetManager->getTexture("player_jump") };

    _idleAnim = Animation(idleFrames, 0.25f);
    _runAnim = Animation(runFrames, 0.10f);
    _jumpAnim = Animation(jumpFrames, 0.18f);
    _currentAnim = &_idleAnim;
}

// Ustawia pozycjê startow¹ gracza
void Player::SetStartPosition(const sf::Vector2f& startPos) {
    _position = startPos;
}

// Obs³uga wejœcia: sprawdza, które klawisze s¹ wciœniête i wywo³uje powi¹zane z nimi komendy
void Player::handleInput(const std::unordered_map<sf::Keyboard::Key, bool>& keystates) {
    _velocity.x = 0;
    for (const auto& [key, command] : commandMap) {
        if (keystates.count(key) && keystates.at(key)) {
            command->Execute(*this);
        }
    }
}

// Aktualizuje pozycjê, animacjê, kolizje (pod³o¿e, platformy), migotanie i cooldowny
void Player::Update(float dt, float groundY, const std::vector<sf::RectangleShape>& platforms) {
    _velocity.y += _gravity * dt;
    sf::Vector2f prevPosition = _position;
    _position += _velocity * dt;

    float playerHeight = 0.f;
    float playerWidth = 0.f;
    if (_currentAnim && _currentAnim->GetCurrentFrame()) {
        playerHeight = _currentAnim->GetCurrentFrame()->getSize().y;
        playerWidth = _currentAnim->GetCurrentFrame()->getSize().x;
    }

    if (blinking) {
        blinkTimer += dt;
        if (blinkTimer >= blinkDuration) {
            blinking = false;
            blinkTimer = 0.0f;
        }
    }

    if (weaponCooldown > 0.0f) weaponCooldown -= dt;

    float prevBottom = prevPosition.y + playerHeight;
    float nextBottom = _position.y + playerHeight;

    _onGround = false;

    // 1. Detekcja pod³o¿a (ziemia)
    if (nextBottom >= groundY) {
        _position.y = groundY - playerHeight;
        _velocity.y = 0.f;
        _onGround = true;
    }

    // 2. Detekcja kolizji z platformami (tylko od góry)
    for (const auto& plat : platforms) {
        sf::FloatRect platRect = plat.getGlobalBounds();
        float platLeft = platRect.left;
        float platRight = platRect.left + platRect.width;

        bool xOverlap = _position.x + playerWidth > platLeft && _position.x < platRight;
        bool wasAbove = prevBottom <= platRect.top;
        bool willBeOnOrBelow = nextBottom >= platRect.top && prevBottom <= platRect.top;

        // Jeœli spadamy, byliœmy nad platform¹ i w³aœnie j¹ przekroczyliœmy oraz jest pokrycie w osi X
        if (_velocity.y > 0 && wasAbove && willBeOnOrBelow && xOverlap) {
            _position.y = platRect.top - playerHeight;
            _velocity.y = 0.f;
            _onGround = true;
            break;
        }
    }

    // Animacja
    Animation* desired = &_idleAnim;
    if (!_onGround) desired = &_jumpAnim;
    else if (_velocity.x != 0.f) desired = &_runAnim;

    if (_currentAnim != desired) {
        _currentAnim = desired;
        _currentAnim->Reset();
    }
    _currentAnim->Update(dt);
}

// Rysuje gracza, obs³uguje efekt migotania (niewidocznoœæ co 0.1s)
void Player::Draw(sf::RenderWindow& window) const {
    if (!_currentAnim) return;
    const sf::Texture* tex = _currentAnim->GetCurrentFrame();
    if (!tex) return;
    sf::Sprite sprite;
    sprite.setTexture(*tex);
    sprite.setPosition(_position);
    sprite.setScale(1.f, 1.f);
    sprite.setOrigin(0.f, 0.f);

    // Migotanie: jeœli blinking i co 0.1s (czyli ~10 razy na sekundê) NIE rysuj
    if (blinking && (static_cast<int>(blinkTimer * 10) % 2 == 0)) {
        // Pomijamy rysowanie (player znika na chwilê)
        return;
    }

    window.draw(sprite);
}

// Zwraca pozycjê gracza
sf::Vector2f Player::GetPosition() const {
    return _position;
}

// Zwraca wysokoœæ sprite'a gracza
float Player::GetHeight() const {
    return _currentAnim->GetCurrentFrame()->getSize().y;
}

// Zwraca rozmiar sprite'a gracza
sf::Vector2u Player::GetSpriteSize() const {
    if (_currentAnim && _currentAnim->GetCurrentFrame()) {
        return _currentAnim->GetCurrentFrame()->getSize();
    }
    return sf::Vector2u(0, 0); // jeœli brak animacji lub tekstury
}

// Zwraca prostok¹t kolizyjny gracza
sf::FloatRect Player::GetCollisionRect() const {
    sf::Vector2f size(0.f, 0.f);
    if (_currentAnim && _currentAnim->GetCurrentFrame()) {
        size.x = _currentAnim->GetCurrentFrame()->getSize().x;
        size.y = _currentAnim->GetCurrentFrame()->getSize().y;
    }
    return sf::FloatRect(_position, size);
}

// Ustawia dŸwiêk skoku gracza
void Player::setJumpSound(sf::Sound* sound) {
    jumpSound = sound;
}

// Ustawia dŸwiêk rzutu no¿em gracza
void Player::setKnifeThrowSound(sf::Sound* sound) {
    knifeThrowSound = sound;
}

// Rozpoczyna efekt migotania na okreœlony czas (po trafieniu)
void Player::startBlink(float duration) {
    blinking = true;
    blinkDuration = duration;
    blinkTimer = 0.0f;
}

// Zwraca, czy gracz obecnie miga (jest nietykalny)
bool Player::isBlinking() const {
    return blinking;
}

// Przesuwa gracza o zadany wektor (np. knockback)
void Player::moveBy(const sf::Vector2f& offset) {
    this->_position.x += offset.x;
    this->_position.y += offset.y;
}

// Zwraca wskaŸnik na dŸwiêk rzutu no¿em
sf::Sound* Player::getKnifeThrowSound() const {
    return knifeThrowSound;
}

// Ogranicza ruch gracza do okreœlonych granic X
void Player::constrainToBounds(float minX, float maxX) {
    if (_position.x < minX) {
        _position.x = minX;
        _velocity.x = 0;
    }
    if (_position.x + _currentAnim->GetCurrentFrame()->getSize().x > maxX) {
        _position.x = maxX - _currentAnim->GetCurrentFrame()->getSize().x;
        _velocity.x = 0;
    }
}

// Zwraca, czy gracz mo¿e rzuciæ broni¹ (cooldown)
bool Player::canShoot() const {
    return weaponCooldown <= 0.0f;
}

// Resetuje cooldown rzutu broni¹
void Player::resetWeaponCooldown() {
    weaponCooldown = weaponCooldownDuration;
}

// Przypisuje komendê do klawisza
void Player::bindCommand(sf::Keyboard::Key key, std::unique_ptr<Command> command) {
    commandMap[key] = std::move(command);
}

// Ruch w lewo
void Player::MoveLeft() {
    _velocity.x = -_moveSpeed;
}

// Ruch w prawo
void Player::MoveRight() {
    _velocity.x = _moveSpeed;
}

// Skok (tylko gdy stoi na ziemi)
void Player::Jump() {
    if (_onGround) {
        if (jumpSound) jumpSound->play();
        _velocity.y = _jumpImpulse;
        _onGround = false;
    }
}

// Rzut broni¹ (np. no¿em), tworzy nowy obiekt Weapon i dodaje do listy
void Player::tryThrowWeapon(sf::Texture* weaponTexture, std::vector<Weapon>& weaponList) {
    sf::Vector2f playerPosition = GetPosition();

    Weapon weapon = Weapon(sf::Vector2f(playerPosition.x, (playerPosition.y + (GetHeight() / 2.f))),
        600.f, 1.5f, weaponTexture);

    weaponList.emplace_back(weapon);

    resetWeaponCooldown();
}