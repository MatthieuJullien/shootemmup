#pragma once
#include "Entity.h"
#include "ResourceIdentifiers.h"

class Aircraft : public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor,
	};

	explicit Aircraft(Type type, const TextureHolder & textures);

private:
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

	Type mType;
	sf::Sprite mSprite;
};

