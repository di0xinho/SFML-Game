#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    bool loadSound(const std::string& name, const std::string& filename);
    bool loadMusic(const std::string& name, const std::string& filename);

    void playSound(const std::string& name);
    void playMusic(const std::string& name);
    void stopMusic(const std::string& name);
    void stopAllMusic(); // Dodajemy deklaracjê metody
    void pauseMusic(const std::string& name);
    void setMusicLoop(const std::string& name, bool loop);

private:
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    std::unordered_map<std::string, sf::Sound> sounds;
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> musics;
};