#include "gold.h"
#include "headers.h"

USING_NS_CC;
USING_NS_CC_EXT;

Gold::~Gold()
{
	m_rotatingAction->release();
}
// on "init" you need to initialize your instance
bool Gold::init(float posX, float posY)
{
	m_x = posX;
	m_y = posY;

	m_spriteSheet = SpriteBatchNode::create("res/gold.png");

	char str[100] = { 0 };
	auto cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames(10);
	for (int i = 0; i < 10; i++)
	{
		sprintf(str, "gold%d.png", i);
		animFrames.pushBack(cache->getSpriteFrameByName(str));
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.15f);
	m_rotatingAction = RepeatForever::create(Animate::create(animation));
	m_rotatingAction->retain();

	m_sprite = PhysicsSprite::createWithSpriteFrameName("gold0.png");
	m_spriteSheet->addChild(m_sprite);
	m_sprite->runAction(m_rotatingAction);



	//physics
	Size contentSize = m_sprite->getContentSize();
	float radius = 0.95 * m_sprite->getContentSize().width / 2;
	m_body = cpBodyNew(0.1f, cpMomentForBox(PHYSICS_INFINITY, contentSize.width, contentSize.height));
	cpBodyApplyImpulseAtLocalPoint(m_body, cpv(0, 150), cpv(0, 0));
	cpBodySetPosition(m_body, cpv(posX, posY));
	m_sprite->setCPBody(m_body);

	m_shape = cpCircleShapeNew(m_body, radius, cpv(0, 0));
	cpShapeSetCollisionType(m_shape, SpriteTag::gold);
	cpShapeSetSensor(m_shape, true);

	return true;
}

void Gold::addToLayer(cpSpace* space, cocos2d::Layer* layer)
{
	m_space = space;
	m_layer = layer;
	m_layer->addChild(m_spriteSheet, 10);

	//cpSpaceAddBody(m_space, m_body);
	cpSpaceAddShape(m_space, m_shape);
}


void Gold::removeFromLayer() {
	float px = m_sprite->getPositionX();
	float py = m_sprite->getPositionY();
	auto action  = MoveTo::create(0.8f, Vec2(px - 200, py + 350));
	auto move_ease_in = EaseBackIn::create(action->clone());
	m_sprite->runAction(move_ease_in);
}
