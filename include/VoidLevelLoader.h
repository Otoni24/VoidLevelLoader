#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace vll
{
	struct GameObjectData
	{
		std::string objectID;
		sf::Vector2f position;
		sf::Vector2f scale;
		sf::Angle rotation;
		sf::Vector2f origin;
	};
	struct LevelData
	{
		std::vector<GameObjectData> gameObjectsData;
		std::vector<std::vector<sf::Vector2f>> hitboxChain;
	};
	std::optional<LevelData> load(std::string path);
}