#pragma once
#include "SceneNode.h"

class SpriteNode : public SceneNode
{
public:
	explicit SpriteNode(const sf::Texture &texture);
	SpriteNode(const sf::Texture &texture, const sf::IntRect &textureRect);

private:
	virtual void drawCurrrent(sf::RenderTarget &target, sf::RenderStates states) const;

	sf::Sprite mSprite;
};

