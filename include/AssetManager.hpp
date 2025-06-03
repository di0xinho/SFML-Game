#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <stdexcept>

// Klasa odpowiadaj¹ca za zarz¹dzanie zasobami gry (tekstury, czcionki)
class AssetManager
{
public:
    AssetManager() {}
    ~AssetManager();

    // £aduje teksturê z pliku i zapisuje pod podan¹ nazw¹
    void loadTexture(const std::string& name, const std::string& fileName);

    // Zwraca referencjê do tekstury o zadanej nazwie
    sf::Texture& getTexture(const std::string& name);

    // £aduje czcionkê z pliku i zapisuje pod podan¹ nazw¹
    void loadFont(const std::string& name, const std::string& fileName);

    // Zwraca referencjê do czcionki o zadanej nazwie
    sf::Font& getFont(const std::string& name);

private:
    // Mapa tekstur (klucz: nazwa tekstury)
    std::map<std::string, sf::Texture> _textures;

    // Mapa czcionek (klucz: nazwa czcionki)
    std::map<std::string, sf::Font> _fonts;
};