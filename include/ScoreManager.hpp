#pragma once
#include <SFML/Graphics.hpp>

class ScoreManager {
public:
    ScoreManager();

    void reset();
    void addPoints(int points);
    int getScore() const;

    void setFont(const sf::Font& font);
    void setPosition(float x, float y);
    void render(sf::RenderWindow& window);

private:
    int score;
    sf::Font font;
    sf::Text scoreText;
};