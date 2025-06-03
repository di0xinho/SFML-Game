#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "State.hpp"
#include "GameData.hpp"
#include "GameConfig.hpp"

// Stan gry odpowiadajπcy za ekran pauzy
class PauseState : public State {
public:
    // Tworzy stan pauzy, przekazujπc wskaünik do danych gry
    PauseState(std::shared_ptr<GameData> data);

    // Inicjalizuje zasoby wymagane przez stan pauzy
    void Init() override;

    // Obs≥uguje wejúcie uøytkownika podczas pauzy
    void HandleInput() override;

    // Aktualizuje logikÍ stanu pauzy
    void Update(float dt) override;

    // Rysuje ekran pauzy
    void Draw(float dt) override;

private:
    std::shared_ptr<GameData> _data;      // Wskaünik do danych gry

    const char* titleText = "PAUZA";      // Tytu≥ ekranu pauzy
    const char* instructionText = "Nacisnij klawisz P, aby kontynuowac rozgrywke"; // Instrukcja na ekranie pauzy
};