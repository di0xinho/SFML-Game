#pragma once

#include "Command.hpp"
#include "Player.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include "Weapon.hpp"

// Klasa reprezentująca polecenie ataku dla gracza (wzorzec Command)
class AttackCommand : public Command {
public:
    // Konstruktor przyjmujący teksturę broni oraz referencję do wektora broni
    AttackCommand(sf::Texture* weaponTexture, std::vector<Weapon>& weapons)
        : weaponTexture(weaponTexture), weapons(weapons) {
    }

    // Wykonuje komendę ataku na przekazanym obiekcie Player
    void Execute(Player& player) override;

private:
    sf::Texture* weaponTexture;      // Wskaźnik na teksturę broni
    std::vector<Weapon>& weapons;    // Referencja do wektora aktywnych broni
};