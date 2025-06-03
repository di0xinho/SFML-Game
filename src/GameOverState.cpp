#include "GameOverState.hpp"

// Konstruktor: zapisuje wskaŸnik do danych gry, koñcowy wynik i informacjê o wygranej/przegranej
GameOverState::GameOverState(std::shared_ptr<GameData> data, int finalScore, bool won)
    : _data(data), _finalScore(finalScore), _won(won) {
}

// Inicjalizacja stanu GameOver - ³adowanie zasobów i ustawienie pozycji
void GameOverState::Init() {
    // Za³aduj teksturê t³a ekranu koñca gry
    _data->assetManager->loadTexture("gameover", GAMEOVER_IMAGE);
    gameOverTexture = &_data->assetManager->getTexture("gameover");
    gameOverSprite.setTexture(*gameOverTexture);

    // Pobierz czcionkê (musi byæ wczeœniej za³adowana)
    font = &_data->assetManager->getFont("robotoFont");

    // Wybierz i za³aduj odpowiedni dŸwiêk w zale¿noœci od wyniku
    std::string soundKey = _won ? "levelPassedSound" : "levelFailedSound";
    std::string soundPath = _won ? LEVEL_PASSED_SOUND : LEVEL_FAILED_SOUND;
    _data->soundManager->loadSound(soundKey, soundPath);
    gameOverSound = &_data->soundManager->getSound(soundKey);

    // Odtwórz dŸwiêk koñca gry
    if (gameOverSound)
        gameOverSound->play();

    // Ustaw pozycjê sprite'a game over (wyœrodkowanie)
    auto winSize = _data->window->getSize();
    auto texSize = gameOverTexture->getSize();
    gameOverSprite.setPosition(
        (float)winSize.x / 2 - texSize.x / 2,
        (float)winSize.y / 2 - texSize.y / 2 - 60
    );
}

// Obs³uguje wejœcie u¿ytkownika - restart gry po naciœniêciu klawisza R
void GameOverState::HandleInput() {
    // Restart gry po naciœniêciu klawisza R
    if (_data->inputManager->isKeyPressed(sf::Keyboard::R)) {
        _data->machine.AddState(std::make_unique<GameState>(_data), true);
        //std::cout << "Kliklem se"<<std::endl;
    }
}

// Brak logiki aktualizacji w tym stanie
void GameOverState::Update(float dt) {}

// Rysuje ekran koñca gry: t³o, tekst, wynik i instrukcjê restartu
void GameOverState::Draw(float dt) {
    auto winSize = _data->window->getSize();

    // T³o (czarne)
    sf::RectangleShape bg(sf::Vector2f((float)winSize.x, (float)winSize.y));
    bg.setFillColor(sf::Color::Black);
    _data->window->draw(bg);

    // Rysuj teksturê t³a GameOver (jeœli jest dostêpna)
    if (gameOverTexture)
        _data->window->draw(gameOverSprite);

    // Wyœwietl odpowiedni komunikat (WYGRALES! lub PRZEGRALES!)
    std::string message = _won ? "WYGRALES!" : "PRZEGRALES!";
    sf::Color msgColor = _won ? sf::Color::Green : sf::Color::Red;
    int msgFontSize = 48;

    sf::Text msgText;
    msgText.setFont(*font);
    msgText.setString(message);
    msgText.setCharacterSize(msgFontSize);
    msgText.setFillColor(msgColor);
    msgText.setStyle(sf::Text::Bold);
    float msgX = winSize.x / 2 - msgText.getLocalBounds().width / 2;
    // Pod GameOverTexture (wyœrodkowanie)
    float textureBottomY = gameOverSprite.getPosition().y + (gameOverTexture ? gameOverTexture->getSize().y : 0);
    msgText.setPosition(msgX, textureBottomY + 40);
    _data->window->draw(msgText);

    // Wyœwietl wynik gracza
    char scoreText[64];
    sprintf(scoreText, "Wynik: %d", _finalScore);
    sf::Text scoreSfText;
    scoreSfText.setFont(*font);
    scoreSfText.setString(scoreText);
    scoreSfText.setCharacterSize(32);
    scoreSfText.setFillColor(sf::Color::White);
    float scoreX = winSize.x / 2 - scoreSfText.getLocalBounds().width / 2;
    scoreSfText.setPosition(scoreX, msgText.getPosition().y + 60);
    _data->window->draw(scoreSfText);

    // Komunikat o restarcie gry
    std::string restartMsg = "Nacisnij klawisz R, aby zrestartowac gre";
    sf::Text restartText;
    restartText.setFont(*font);
    restartText.setString(restartMsg);
    restartText.setCharacterSize(24);
    restartText.setFillColor(sf::Color::Yellow);
    float restartX = winSize.x / 2 - restartText.getLocalBounds().width / 2;
    restartText.setPosition(restartX, msgText.getPosition().y + 110);
    _data->window->draw(restartText);
}