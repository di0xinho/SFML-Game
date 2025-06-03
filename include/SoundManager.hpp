#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <memory>
#include <stdexcept>

// Klasa zarz¹dzaj¹ca dŸwiêkami i muzyk¹ w grze
// Pozwala ³adowaæ, pobieraæ i zarz¹dzaæ zasobami dŸwiêkowymi oraz muzycznymi
class SoundManager {
public:
    SoundManager() = default;
    ~SoundManager();

    // £aduje dŸwiêk z pliku i przypisuje mu nazwê
    void loadSound(const std::string& name, const std::string& filename);

    // Zwraca referencjê do za³adowanego dŸwiêku na podstawie nazwy
    sf::Sound& getSound(const std::string& name);

    // £aduje muzykê z pliku i przypisuje jej nazwê
    void loadMusic(const std::string& name, const std::string& filename);

    // Zwraca referencjê do za³adowanej muzyki na podstawie nazwy
    sf::Music& getMusic(const std::string& name);

private:
    // Bufory dŸwiêku (musz¹ ¿yæ tak d³ugo jak dŸwiêki)
    std::map<std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers;

    // DŸwiêki
    std::map<std::string, std::unique_ptr<sf::Sound>> sounds;

    // Muzyka (sf::Music trzymamy na wskaŸnikach)
    std::map<std::string, std::unique_ptr<sf::Music>> musics;
};