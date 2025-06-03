#include "Player.hpp"
#include "AttackCommand.hpp"

// Wykonuje komendę ataku - rzut nożem, jeśli możliwe
void AttackCommand::Execute(Player& player) {
    // Jeśli gracz może rzucić bronią (nie trwa cooldown)
    if (player.canShoot()) {
        // Rzuć bronią (np. nożem)
        player.tryThrowWeapon(weaponTexture, weapons);

        // Odtwórz dźwięk rzutu nożem, jeśli jest ustawiony
        if (auto sound = player.getKnifeThrowSound()) {
            sound->play();
        }
    }
}