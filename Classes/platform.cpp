#include "platform.h"
#include "headers.h"

USING_NS_CC;
USING_NS_CC_EXT;
Platform::~Platform()
{
	cpSpaceRemoveBody(m_space, m_body);
}

// on "init" you need to initialize your instance
bool Platform::init(float boardX, float boardY, int length)
{
	m_length = length;

	//create platform
	m_spriteSheet = SpriteBatchNode::create("res/platform.png");
	char str[100] = { 0 };
	sprintf(str, "platform_%d.png", (int)length);
	m_sprite = PhysicsSprite::createWithSpriteFrameName(str);
	m_spriteSheet->addChild(m_sprite);


	Size cSize = m_sprite->getContentSize();
	m_width = cSize.width;
	boardX += cSize.width / 2;

	m_body = cpBodyNew(0, 0);
	cpBodySetType(m_body, CP_BODY_TYPE_STATIC);
	cpBodySetPosition(m_body, cpv(boardX, boardY));
	m_sprite->setCPBody(m_body);

	m_shape = cpBoxShapeNew(m_body, cSize.width, cSize.height, 0);
	cpShapeSetCollisionType(m_shape, SpriteTag::platform);
	cpShapeSetElasticity(m_shape, 0);

	return true;
}

void Platform::addToLayer(cpSpace* space, cocos2d::Layer* layer)
{
	m_space = space;
	m_layer = layer;
	m_layer->addChild(m_spriteSheet);

	cpSpaceAddBody(m_space, m_body);
	cpSpaceAddShape(m_space, m_shape);
}


void Platform::removeFromLayer() {

	m_sprite->removeFromParent();
	m_spriteSheet->removeFromParent();
}

float Platform::getLastX() {
	return m_sprite->getPositionX() + m_width / 2;
}

float Platform::getX() {
	return m_sprite->getPositionX() - m_width / 2;
}

int Platform::getLength() {
	return m_length;
}