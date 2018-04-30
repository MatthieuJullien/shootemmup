#pragma once
#include <array>
#include <SFML\Graphics.hpp>
#include "ResourceIdentifiers.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "Aircraft.h"


// Forward declaration
//namespace sf
//{
//	class RenderWindow;
//}

class World : private sf::NonCopyable
{
public:
	explicit							World(sf::RenderWindow& window);
	void								update(sf::Time dt);
	void								draw();


private:
	void								loadTextures();
	void								buildScene();


private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};


private:
	sf::RenderWindow&					mWindow;
	sf::View							mWorldView;
	TextureHolder						mTextures;

	SceneNode							mSceneGraph;
	std::array<SceneNode*, Layer::LayerCount>	mSceneLayers;

	sf::FloatRect						mWorldBounds;
	sf::Vector2f						mSpawnPosition;
	float								mScrollSpeed;
	Aircraft*							mPlayerAircraft;
};
