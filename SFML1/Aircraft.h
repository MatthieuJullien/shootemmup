#pragma once
#include "Entity.h"
#include "Category.h"
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
	virtual unsigned int	getCategory() const;

private:
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

	Type mType;
	sf::Sprite mSprite;
};

