#include "ScoreManager.hpp"

ScoreManager::ScoreManager() : score(0) {
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Score: 0");
}

void ScoreManager::reset() {
    score = 0;
    scoreText.setString("Score: 0");
}

void ScoreManager::addPoints(int points) {
    score += points;
    scoreText.setString("Score: " + std::to_string(score));
}

int ScoreManager::getScore() const {
    return score;
}

void ScoreManager::setFont(const sf::Font& font) {
    this->font = font;
    scoreText.setFont(this->font);
}

void ScoreManager::setPosition(float x, float y) {
    scoreText.setPosition(x, y);
}

void ScoreManager::render(sf::RenderWindow& window) {
    window.draw(scoreText);
}