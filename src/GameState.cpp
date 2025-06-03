#include "GameState.hpp"

// Konstruktor: zapisuje wskaŸnik do struktury z danymi gry
GameState::GameState(std::shared_ptr<GameData> data)
    : _data(data) {
}

// Inicjalizacja stanu gry: ³adowanie assetów, przygotowanie obiektów gry, ustawienia startowe
void GameState::Init() {
    // --- Assety: tekstury, fonty, dŸwiêki ---
    // T³a i pod³o¿e
    _data->assetManager->loadTexture("background", BACKGROUND_TEXTURE);
    _data->assetManager->loadTexture("land", LAND_TEXTURE);

    // Gracz
    const std::vector<std::pair<std::string, std::string>> playerTextures = {
        {"player_idle", PLAYER_IDLE},
        {"player_run_1", PLAYER_RUN_1},
        {"player_run_2", PLAYER_RUN_2},
        {"player_run_3", PLAYER_RUN_3},
        {"player_jump", PLAYER_JUMP}
    };
    for (const auto& [name, path] : playerTextures)
        _data->assetManager->loadTexture(name, path);

    // Broñ, wrogowie, font
    _data->assetManager->loadTexture("weapon", SWORD_TEXTURE);
    _data->assetManager->loadTexture("enemy_1", ENEMY_1);
    _data->assetManager->loadTexture("enemy_2", ENEMY_2);
    font = &_data->assetManager->getFont("robotoFont");

    // DŸwiêki
    const std::vector<std::pair<std::string, std::string>> sounds = {
        {"enemy_hit", OUCH_SOUND},
        {"punch_sound", PUNCH_SOUND},
        {"jump_sound", JUMP_SOUND},
        {"coin_collected", COIN_SOUND},
        {"knife_throw_sound", KNIFE_THROW_SOUND}
    };
    for (const auto& [name, path] : sounds)
        _data->soundManager->loadSound(name, path);

    _data->soundManager->loadMusic("game_music", GAME_MUSIC);

    // --- Przypisanie wskaŸników do dŸwiêków i muzyki ---
    punchSound = &_data->soundManager->getSound("punch_sound");
    gameMusic = &_data->soundManager->getMusic("game_music");

    // --- Ustawienie t³a i pod³o¿a ---
    _background.setTexture(_data->assetManager->getTexture("background"));
    _background.setPosition(0.f, 0.f);

    _land.setTexture(_data->assetManager->getTexture("land"));
    _land.setScale(3.2f, 1.0f);
    float landY = _data->window->getSize().y - _land.getTexture()->getSize().y;
    _land.setPosition(0.f, landY);

    // --- Gracz ---
    _player.Init(_data);
    _player.SetStartPosition(sf::Vector2f(80.f, landY - _player.GetSpriteSize().y));
    _player.setJumpSound(&_data->soundManager->getSound("jump_sound"));
    _player.setKnifeThrowSound(&_data->soundManager->getSound("knife_throw_sound"));

    // --- Platformy ---
    platforms.clear();
    const std::vector<PlatformData> platformData = {
        {{140, 20}, {200, 400}, {120, 120, 120}},
        {{100, 20}, {400, 380}, {150, 100, 100}},
        {{180, 20}, {600, 400}, {100, 150, 120}},
        {{140, 20}, {800, 340}, {100, 150, 120}},
        {{160, 20}, {1000, 300}, {255, 0, 0}},
        {{160, 20}, {1300, 300}, {0, 255, 0}},
        {{160, 20}, {1500, 320}, {0, 0, 255}},
        {{120, 20}, {1800, 380}, {0, 255, 255}}
    };
    for (const auto& pd : platformData)
        platforms.push_back(makePlatform(pd.size, pd.pos, pd.color));

    // --- Monety (animacja, pozycje, dŸwiêk) ---
    coins.clear();
    const char* coinPaths[] = {
        COIN_1, COIN_2, COIN_3, COIN_4, COIN_5, COIN_6, COIN_7,
        COIN_8, COIN_9, COIN_10, COIN_11, COIN_12, COIN_13, COIN_14
    };
    std::vector<const sf::Texture*> coinFrames;
    for (int i = 1; i <= 14; ++i) {
        std::string name = "COIN_" + std::to_string(i);
        _data->assetManager->loadTexture(name, coinPaths[i - 1]);
        coinFrames.push_back(&(_data->assetManager->getTexture(name)));
    }
    const sf::Vector2f coinPositions[] = {
        {270, 360}, {450, 340}, {690, 360}, {870, 300},
        {1080, 260}, {1380, 260}, {1580, 280}, {1860, 340}
    };
    for (const auto& pos : coinPositions) {
        Coin coin(pos, coinFrames);
        coin.setCollectedCoinSound(&_data->soundManager->getSound("coin_collected"));
        coins.emplace_back(coin);
    }

    // --- Wrogowie (animacja, pozycje, dŸwiêk) ---
    enemies.clear();
    std::vector<const sf::Texture*> enemyFrames;
    for (int i = 1; i <= 2; ++i)
        enemyFrames.push_back(&(_data->assetManager->getTexture("enemy_" + std::to_string(i))));
    const sf::Vector2f enemyPositions[] = {
        {600, landY - 32.f},
        {1000, landY - 32.f},
        {1400, landY - 32.f},
        {1700, landY - 32.f}
    };
    for (const auto& pos : enemyPositions) {
        Enemy enemy(pos, enemyFrames);
        enemy.setHitSound(&_data->soundManager->getSound("enemy_hit"));
        enemies.emplace_back(enemy);
    }

    // --- HUD ---
    _hud.Init(font);
    _hud.SetScore(0);
    _hud.SetLives(lives);

    // --- Trofeum ---
    _data->assetManager->loadTexture("TROPHY", TROPHY);
    trophy = Trophy(sf::Vector2f(2100, 230), &_data->assetManager->getTexture("TROPHY"));

    // --- Tekstura broni ---
    weaponTexture = &_data->assetManager->getTexture("weapon");

    // --- Kamera ---
    sf::Vector2u winSize = _data->window->getSize();
    _camera.setSize(static_cast<float>(winSize.x), static_cast<float>(winSize.y));
    _camera.zoom(0.6f);
    _camera.setCenter(_player.GetPosition());

    // --- Muzyka ---
    gameMusic->setLoop(true);
    gameMusic->play();

    // --- Komendy gracza (wzorzec Command) ---
    _player.bindCommand(sf::Keyboard::Left, std::make_unique<MoveLeftCommand>());
    _player.bindCommand(sf::Keyboard::Right, std::make_unique<MoveRightCommand>());
    _player.bindCommand(sf::Keyboard::Space, std::make_unique<JumpCommand>());
    _player.bindCommand(sf::Keyboard::Enter, std::make_unique<AttackCommand>(weaponTexture, weapons));
}

// Obs³uguje wejœcie u¿ytkownika: pauza gry, sterowanie gracza (komendy)
void GameState::HandleInput() {
    // Pauza po escapie
    if (_data->inputManager->isKeyPressed(sf::Keyboard::Escape)) {
        gameMusic->pause();
        _data->machine.AddState(std::make_unique<PauseState>(_data), false);
    }

    // Obs³uga komend gracza (wzorzec Command)
    std::unordered_map<sf::Keyboard::Key, bool> keystates;
    for (const auto& [key, _] : _player.commandMap) {
        keystates[key] = _data->inputManager->isKeyPressed(key);
    }
    _player.handleInput(keystates);
}

// Aktualizuje logikê gry: ruchy, kolizje, punkty, zwyciêstwo/przegrana itp.
void GameState::Update(float dt) {
    // Wylicz groundY na podstawie sprite’a land
    float landY = _land.getPosition().y;
    float groundY = landY; // Poziom "ziemi", do którego postaæ mo¿e stan¹æ

    _player.Update(dt, groundY, platforms);
    _player.constrainToBounds(0, 2200);

    // Obs³uga monet
    for (auto& coin : coins) {
        coin.Update(dt);

        sf::FloatRect playerRect = _player.GetCollisionRect();

        // Kolizja gracza z monet¹
        if (!coin.IsCollected() && coin.GetCollisionRect().intersects(playerRect))
        {
            coin.Collect();
            score++;
            _hud.SetScore(score);
        }
    }

    // Obs³uga wrogów
    for (auto& enemy : enemies) {
        enemy.Update(dt, groundY);

        sf::FloatRect enemyRect = enemy.GetCollisionRect();

        // SprawdŸ kolizjê gracza z wrogiem
        if (!_player.isBlinking() && enemy.IsAlive() && _player.GetCollisionRect().intersects(enemyRect)) {
            punchSound->play();
            lives--;
            _hud.SetLives(lives);
            _player.startBlink(1.0f);

            sf::Vector2f knockback;
            if (enemy.GetPosition().x < _player.GetPosition().x)
                knockback = { 80.f, -60.f };  // odrzuæ w prawo
            else
                knockback = { -80.f, -60.f }; // odrzuæ w lewo

            _player.moveBy(knockback);

            if (lives <= 0) {
                gameMusic->stop();
                _data->machine.AddState(std::make_unique<GameOverState>(_data, score, false), true);
            }
        }
    }

    // Obs³uga broni i trafieñ wrogów
    for (Weapon& weapon : weapons) {
        weapon.Update(dt, enemies);
        for (Enemy& enemy : enemies) {
            if (enemy.IsAlive() && weapon.CollidesWith(enemy)) {
                weapon.Kill();
                enemy.Hit();
            }
        }
    }
    // Usuñ nieaktywne pociski
    weapons.erase(
        std::remove_if(weapons.begin(), weapons.end(), [](const Weapon& w) { return !w.IsAlive(); }),
        weapons.end()
    );

    // Usuwanie martwych wrogów
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) { return !e.IsAlive(); }),
        enemies.end());

    // Aktualizacja trofeum (animacja itp.)
    trophy.Update(dt);

    sf::FloatRect playerRect = _player.GetCollisionRect();

    // Kolizja gracza z trofeum (wygrana)
    if (trophy.GetCollisionRect().intersects(playerRect)) {
        gameMusic->stop();
        _data->machine.AddState(std::make_unique<GameOverState>(_data, score, true), true);
    }

    // Obs³uga kamery - p³ynne przesuwanie za graczem
    sf::Vector2f camCenter = _camera.getCenter();
    sf::Vector2f playerPos = _player.GetPosition();

    // P³ynnie przesuwaj kamerê w poziomie 
    camCenter.x += (playerPos.x - camCenter.x) * 0.1f;

    // Ogranicz kamerê, ¿eby nie przesuwa³a siê w lewo poza mapê
    float minCamX = _camera.getSize().x / 2.f;
    if (camCenter.x < minCamX)
        camCenter.x = minCamX;

    _camera.setCenter(camCenter.x, camCenter.y);
}

// Rysowanie ca³ego stanu gry: t³o, obiekty, hud
void GameState::Draw(float dt) {
    // Najpierw t³o
    _data->window->setView(_camera);

    sf::Vector2f viewTopLeft = _camera.getCenter() - _camera.getSize() / 2.f;
    _background.setPosition(viewTopLeft);
    _data->window->draw(_background);

    // Nastêpnie pod³o¿e
    _data->window->draw(_land);

    // Gracz
    _player.Draw(*_data->window);

    // Platformy
    for (const auto& plat : platforms)
        _data->window->draw(plat);

    // Monety
    for (const auto& coin : coins)
        coin.Draw(*_data->window);

    // Wrogowie
    for (const auto& enemy : enemies) {
        if (enemy.IsAlive())
            enemy.Draw(*_data->window);
    }

    // Broñ (pociski)
    for (const Weapon& weapon : weapons) {
        weapon.Draw(*_data->window);
    }

    // Trofeum
    trophy.Draw(*_data->window);

    // Hud (przywróæ widok domyœlny)
    _data->window->setView(_data->window->getDefaultView());
    _hud.Draw(*_data->window);
}

// Wznawia muzykê po powrocie do stanu gry
void GameState::resume() {
    gameMusic->play();
}