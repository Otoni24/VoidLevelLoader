#include "VoidLevelLoader.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace vll
{
	std::optional<LevelData> load(std::string path)
	{
		std::ifstream fileStream(path);
		if (!fileStream.is_open()) {
			std::cerr << "LevelLoader Error: Could not open file " << path << std::endl;
			return std::nullopt;
		}

		json data;
		try
		{
			fileStream >> data;
		}
		catch (json::parse_error& e) {
			std::cerr << "LevelLoader Error: JSON parse error in " << path << ": " << e.what() << std::endl;
			return std::nullopt;
		}

		LevelData levelData;

		try
		{
			const auto& gameObjectsJson = data.at("gameObjects");

			for (const auto& goJson : gameObjectsJson)
			{
				GameObjectData goData;

				goData.objectID = goJson.at("assetID").get<std::string>();

				const auto& positionJson = goJson.at("position");
				goData.position.x = positionJson.at("x").get<float>();
				goData.position.y = positionJson.at("y").get<float>();

				const auto& scaleJson = goJson.at("scale");
				goData.scale.x = scaleJson.at("x").get<float>();
				goData.scale.y = scaleJson.at("y").get<float>();

				const auto& originJson = goJson.at("origin");
				goData.origin.x = originJson.at("x").get<float>();
				goData.origin.y = originJson.at("y").get<float>();

				const auto& rotationJson = goJson.at("rotation");
				goData.rotation = sf::degrees(rotationJson.at("degrees").get<float>());

				levelData.gameObjectsData.push_back(goData);
			}

			const auto& hitboxMapJson = data.at("hitboxMap");

			for (const auto& chainJson : hitboxMapJson)
			{
				std::vector<sf::Vector2f> chainData;

				const auto& verticesJson = chainJson.at("vertices");

				for (const auto& vertexJson : verticesJson)
				{
					sf::Vector2f vertexData;

					const auto& vertexPosJson = vertexJson.at("position");

					vertexData.x = vertexPosJson.at("x").get<float>();
					vertexData.y = vertexPosJson.at("y").get<float>();

					chainData.push_back(vertexData);
				}
				levelData.hitboxChain.push_back(chainData);
			}
		}
		catch (json::exception& e)
		{
			std::cerr << "LevelLoader Error: JSON structure error: " << e.what() << std::endl;
			return std::nullopt;
		}

		return levelData;
	}
}