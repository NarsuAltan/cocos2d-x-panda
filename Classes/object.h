#pragma once
#include "cocos2d.h"
#include "chipmunk/chipmunk.h"
#include "extensions/cocos-ext.h"

class GameObject
{
public:
	virtual ~GameObject();

	virtual void addToLayer(cpSpace* space, cocos2d::Layer* layer) {}

	cocos2d::Layer* getLayer() { return m_layer; }

	cpBody* getBody() { return m_body; }

	cpShape* getShape() { return m_shape; }

	float getLastX() {  return 0.0f; }

	float getX() { return m_sprite->getPositionX(); }

	float getY() { return m_sprite->getPositionY();}

	cocos2d::extension::PhysicsSprite* getSprite() { return m_sprite; }


protected:
	// renderer related.
	cocos2d::SpriteBatchNode*				m_spriteSheet;
	cocos2d::extension::PhysicsSprite*		m_sprite;
	cocos2d::Layer*			m_layer;

	// physics related.
	cpSpace*	m_space;
	cpBody*		m_body;
	cpShape*	m_shape;

};
