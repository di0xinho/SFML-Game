#include "Animation.hpp"

// Konstruktor domyœlny animacji
Animation::Animation() {}

// Konstruktor animacji z podanymi klatkami i czasem trwania klatki
Animation::Animation(const std::vector<const sf::Texture*>& frames, float frameTime)
    : _frames(frames), _frameTime(frameTime), _timer(0.f), _currentFrame(0) {
}

// Ustawia nowe klatki animacji oraz czas trwania pojedynczej klatki
void Animation::SetFrames(const std::vector<const sf::Texture*>& frames, float frameTime) {
    _frames = frames;
    _frameTime = frameTime;
    _timer = 0.f;
    _currentFrame = 0;
}

// Aktualizuje animacjê (przechodzi do nastêpnej klatki, jeœli min¹³ czas)
void Animation::Update(float dt) {
    if (_frames.empty()) return;

    _timer += dt;
    if (_timer >= _frameTime) {
        _timer -= _frameTime;
        ++_currentFrame;
        if (_currentFrame >= _frames.size())
            _currentFrame = 0;
    }
}

// Resetuje animacjê do pierwszej klatki
void Animation::Reset() {
    _timer = 0.f;
    _currentFrame = 0;
}

// Zwraca wskaŸnik do aktualnej klatki animacji
const sf::Texture* Animation::GetCurrentFrame() const {
    if (_frames.empty()) return nullptr;
    return _frames[_currentFrame];
}

// Zwraca indeks aktualnej klatki
std::size_t Animation::GetCurrentFrameIndex() const {
    return _currentFrame;
}