#include "PauseState.hpp"

// Konstruktor: zapisuje wskaünik do danych gry
PauseState::PauseState(std::shared_ptr<GameData> data) : _data(data) {}

// Inicjalizacja stanu pauzy (tu pusta, bo nic nie trzeba ≥adowaÊ)
void PauseState::Init() {}

// Brak logiki aktualizacji w tym stanie
void PauseState::Update(float dt) {}

// Obs≥uga wejúcia: zdjÍcie pauzy po naciúniÍciu klawisza P
void PauseState::HandleInput() {
    if (_data->inputManager->isKeyPressed(sf::Keyboard::P)) {
        // Zdejmij stan pauzy (wrÛÊ do poprzedniego stanu)
        _data->machine.RemoveState();
    }
}

// Rysuje ekran pauzy: pÛ≥przezroczyste t≥o, tytu≥ i instrukcjÍ
void PauseState::Draw(float dt) {
    // T≥o pÛ≥przezroczyste
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f((float)_data->window->getSize().x, (float)_data->window->getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 153)); // 60% przezroczystoúci

    _data->window->draw(overlay);

    // Tytu≥
    sf::Text title;
    title.setFont(_data->assetManager->getFont("robotoFont")); // Za≥aduj czcionkÍ w GameState lub globalnie!
    title.setString(titleText);
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);
    float titleX = (_data->window->getSize().x - title.getLocalBounds().width) / 2.f;
    title.setPosition(titleX, 200);

    // Instrukcja
    sf::Text instruction;
    instruction.setFont(_data->assetManager->getFont("robotoFont"));
    instruction.setString(instructionText);
    instruction.setCharacterSize(30);
    instruction.setFillColor(sf::Color(128, 128, 128));
    float instrX = (_data->window->getSize().x - instruction.getLocalBounds().width) / 2.f;
    instruction.setPosition(instrX, 300);

    _data->window->draw(title);
    _data->window->draw(instruction);
}