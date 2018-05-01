#include <algorithm>
#include <cassert>
#include "SceneNode.h"

SceneNode::SceneNode()
	: mChildren()
	, mParent(nullptr)
{}

void SceneNode::attachChild(PtrSceneNode child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::PtrSceneNode SceneNode::detachChild(const SceneNode & node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
		[&](PtrSceneNode &p) -> bool { return p.get() == &node; });
	assert(found != mChildren.end());

	PtrSceneNode result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt)
{
	// Do nothing by default
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (PtrSceneNode &child : mChildren)
	{
		child->update(dt);
	}
}

void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();

	// Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const PtrSceneNode& child : mChildren)
	{
		child->draw(target, states);
	}
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;

	return transform;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	// Command current node, if category matches
	if (command.category & getCategory())
		command.action(*this, dt);

	// Command children
	for (PtrSceneNode& child : mChildren)
		child->onCommand(command, dt);
}

unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}
