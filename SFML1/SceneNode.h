#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include <vector>
#include "Command.h"
#include "Category.h"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> PtrSceneNode;

	SceneNode();
	void attachChild(PtrSceneNode child);
	PtrSceneNode detachChild(const SceneNode &node);
	void update(sf::Time dt);
	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;
	void					onCommand(const Command& command, sf::Time dt);
	virtual unsigned int	getCategory() const;

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final;
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);

	std::vector<PtrSceneNode> mChildren;
	SceneNode *mParent;
};

