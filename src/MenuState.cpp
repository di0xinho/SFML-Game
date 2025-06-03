#include "MenuState.hpp"

// Konstruktor: zapisuje wskaünik do danych gry, zeruje wskaüniki na font i muzykÍ
MenuState::MenuState(std::shared_ptr<GameData> data)
    : _data(data), robotoFont(nullptr), menuMusic(nullptr) {
}

// Inicjalizacja stanu menu: ≥adowanie assetÛw, ustawianie pozycji, uruchamianie muzyki
void MenuState::Init()
{
    // £adowanie tekstur i fontÛw przez AssetManagera (z wykorzystaniem makr)
    _data->assetManager->loadTexture("background_2", BACKGROUND_TEXTURE_2);
    _data->assetManager->loadTexture("play_button", PLAY_BUTTON);

    _data->assetManager->loadFont("robotoFont", ROBOTO_FONT);
    robotoFont = &_data->assetManager->getFont("robotoFont");

    // Przypisanie tekstur do sprite'Ûw
    backgroundSprite.setTexture(_data->assetManager->getTexture("background_2"));
    playButtonSprite.setTexture(_data->assetManager->getTexture("play_button"));

    // Pozycjonowanie przycisku
    float btnWidth = playButtonSprite.getTexture()->getSize().x * buttonScale;
    float btnHeight = playButtonSprite.getTexture()->getSize().y * buttonScale;
    playButtonSprite.setScale(buttonScale, buttonScale);
    playButtonSprite.setPosition(
        (float)(WINDOW_WIDTH / 2 - btnWidth / 2),
        (float)(WINDOW_HEIGHT / 2 - btnHeight / 2)
    );

    // £adowanie muzyki
    _data->soundManager->loadMusic("menuMusic", MENU_MUSIC);
    menuMusic = &_data->soundManager->getMusic("menuMusic");

    // Odtwarzanie muzyki w pÍtli
    menuMusic->setLoop(true);
    menuMusic->play();
}

// Obs≥uga wejúcia: klikniÍcie w przycisk startu gry
void MenuState::HandleInput()
{
    // Obs≥uga klikniÍcia w przycisk
    auto mousePos = sf::Mouse::getPosition(*_data->window);
    sf::FloatRect playBtnRect = playButtonSprite.getGlobalBounds();

    if (_data->inputManager->isRectClicked(playBtnRect, sf::Mouse::Left, *_data->window))
    {
        // Przejdü do GameState
        menuMusic->stop();
        _data->machine.AddState(std::make_unique<GameState>(_data), true);
    }
}

// Brak logiki aktualizacji w tym stanie (muzyka gra automatycznie)
void MenuState::Update(float dt)
{
    // Muzyka jest automatycznie aktualizowana przez SFML
}

// Rysuje t≥o, przycisk oraz napis nad przyciskiem
void MenuState::Draw(float dt)
{
    // T≥o
    _data->window->draw(backgroundSprite);

    // Przycisk
    _data->window->draw(playButtonSprite);

    // Napis nad przyciskiem
    std::string infoText = "Nacisnij guzik, aby wystartowac gre";
    sf::Text infoSfText;
    infoSfText.setFont(*robotoFont);
    infoSfText.setString(infoText);
    infoSfText.setCharacterSize(fontSize);
    infoSfText.setFillColor(sf::Color(64, 64, 64));

    // Pozycjonowanie napisu (nad przyciskiem)
    sf::FloatRect textRect = infoSfText.getLocalBounds();
    float posX = WINDOW_WIDTH / 2 - textRect.width / 2;
    float posY = playButtonSprite.getPosition().y - fontSize - 20;
    infoSfText.setPosition(posX, posY);

    _data->window->draw(infoSfText);
}