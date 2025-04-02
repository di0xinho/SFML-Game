#include "SoundManager.hpp"

SoundManager::SoundManager() {}

SoundManager::~SoundManager() {}

bool SoundManager::loadSound(const std::string& name, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        return false;
    }
    soundBuffers[name] = buffer;
    sounds[name].setBuffer(soundBuffers[name]);
    return true;
}

bool SoundManager::loadMusic(const std::string& name, const std::string& filename) {
    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(filename)) {
        return false;
    }
    musics[name] = std::move(music);
    return true;
}

void SoundManager::playSound(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name].play();
    }
}

void SoundManager::playMusic(const std::string& name) {
    stopAllMusic(); // Zatrzymujemy wszystkie odtwarzane utwory przed rozpoczêciem nowego
    if (musics.find(name) != musics.end()) {
        musics[name]->play();
    }
}

void SoundManager::stopMusic(const std::string& name) {
    if (musics.find(name) != musics.end()) {
        musics[name]->stop();
    }
}

void SoundManager::stopAllMusic() {
    for (auto& music : musics) {
        music.second->stop();
    }
}

void SoundManager::pauseMusic(const std::string& name) {
    if (musics.find(name) != musics.end()) {
        musics[name]->pause();
    }
}

void SoundManager::setMusicLoop(const std::string& name, bool loop) {
    if (musics.find(name) != musics.end()) {
        musics[name]->setLoop(loop);
    }
}