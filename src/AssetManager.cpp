#include "AssetManager.hpp"

// £adowanie tekstury z pliku i dodanie do mapy
void AssetManager::loadTexture(const std::string& name, const std::string& fileName)
{
    sf::Texture tex;
    if (!tex.loadFromFile(fileName))
    {
        throw std::runtime_error("Nie udalo sie zaladowac tekstury " + fileName);
    }
    _textures[name] = std::move(tex);
}

// Pobieranie tekstury po nazwie (wyrzucany wyj¹tek jeœli brak)
sf::Texture& AssetManager::getTexture(const std::string& name)
{
    auto it = _textures.find(name);
    if (it == _textures.end())
        throw std::runtime_error("Nie znaleziono tekstury: " + name);
    return it->second;
}

// £adowanie czcionki z pliku i dodanie do mapy
void AssetManager::loadFont(const std::string& name, const std::string& fileName)
{
    sf::Font font;
    if (!font.loadFromFile(fileName))
    {
        throw std::runtime_error("Nie udalo sie zaladowac czcionki " + fileName);
    }
    _fonts[name] = std::move(font);
}

// Pobieranie czcionki po nazwie (wyrzuca wyj¹tek jeœli brak)
sf::Font& AssetManager::getFont(const std::string& name)
{
    auto it = _fonts.find(name);
    if (it == _fonts.end())
        throw std::runtime_error("Czcionka nie znaleziona: " + name);
    return it->second;
}

// Destruktor: SFML sam zwalnia zasoby, wiêc nie musisz tego robiæ rêcznie
AssetManager::~AssetManager() = default;