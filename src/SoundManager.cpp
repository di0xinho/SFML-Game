#include "SoundManager.hpp"

// Destruktor SoundManagera
SoundManager::~SoundManager() {}

// £aduje dŸwiêk z pliku i przypisuje go do oryginalnej nazwy
void SoundManager::loadSound(const std::string& name, const std::string& filename) {
    auto buffer = std::make_unique<sf::SoundBuffer>();
    if (!buffer->loadFromFile(filename))
        throw std::runtime_error("Nie udalo sie zaladowac dzwieku: " + filename);

    auto sound = std::make_unique<sf::Sound>();
    sound->setBuffer(*buffer);

    soundBuffers[name] = std::move(buffer);
    sounds[name] = std::move(sound);
}

// Zwraca referencjê do dŸwiêku o podanej nazwie
sf::Sound& SoundManager::getSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it == sounds.end()) throw std::runtime_error("Dzwiek nie zostal znaleziony: " + name);
    return *(it->second);
}

// £aduje muzykê z pliku i przypisuje j¹ do oryginalnej nazwy
void SoundManager::loadMusic(const std::string& name, const std::string& filename) {
    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(filename))
        throw std::runtime_error("Nie udalo sie zaladowac muzyki: " + filename);
    musics[name] = std::move(music);
}

// Zwraca referencjê do muzyki o podanej nazwie
sf::Music& SoundManager::getMusic(const std::string& name) {
    auto it = musics.find(name);
    if (it == musics.end()) throw std::runtime_error("Muzyka nie zostala znaleziona: " + name);
    return *(it->second);
}