#pragma once

#include <iostream>

namespace vll
{
	struct Vec2f
	{
		float x;
		float y;
	};
	struct GameObjectData
	{
		std::string objectID;
		Vec2f position;
		Vec2f scale;
		float rotationDegrees;
		Vec2f origin;
	};
	struct LevelData
	{
		std::vector<GameObjectData> gameObjectsData;
		std::vector<std::vector<Vec2f>> hitboxChain;
	};
	std::optional<LevelData> load(std::string path);
}