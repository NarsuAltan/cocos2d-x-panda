#include "frog.h"
#include "headers.h"

USING_NS_CC;
USING_NS_CC_EXT;

Frog::~Frog()
{
}
// on "init" you need to initialize your instance
bool Frog::init(float posX, float posY)
{

	m_x = posX;
	m_y = posY;

	m_spriteSheet = SpriteBatchNode::create("res/enemy.png");

	char str[100] = { 0 };
	auto cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames(6);
	for (int i = 0; i < 6; i++)
	{
		sprintf(str, "enemy_frog_%d.png", i + 1);
		animFrames.pushBack(cache->getSpriteFrameByName(str));
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.15f);
	m_frogAction = RepeatForever::create(Animate::create(animation));
	m_frogAction->retain();

	m_sprite = PhysicsSprite::createWithSpriteFrameName("enemy_frog_1.png");
	m_spriteSheet->addChild(m_sprite);
	m_sprite->runAction(m_frogAction);


	m_runningSpeed = -int(CCRANDOM_0_1() * 10 + 1);

	//physics
	Size contentSize = m_sprite->getContentSize();
	m_body = cpBodyNew(0.1f, cpMomentForBox(PHYSICS_INFINITY, contentSize.width, contentSize.height));
	cpBodyApplyImpulseAtLocalPoint(m_body, cpv(m_runningSpeed, 0), cpv(0, 0));
	cpBodyApplyForceAtLocalPoint(m_body, cpv(0, 150), cpv(0, 0));
	cpBodySetPosition(m_body, cpv(posX, posY));
	m_sprite->setCPBody(m_body);


	m_shape = cpBoxShapeNew(m_body, contentSize.width - 14, contentSize.height - 28, 0);
	cpShapeSetElasticity(m_shape, 0);
	cpShapeSetCollisionType(m_shape, SpriteTag::frog);
	cpShapeSetSensor(m_shape, true);

	return true;
}

void Frog::addToLayer(cpSpace* space, cocos2d::Layer* layer)
{
	m_space = space;
	m_layer = layer;
	m_layer->addChild(m_spriteSheet, 9);

	//cpSpaceAddBody(m_space, m_body);
	cpSpaceAddShape(m_space, m_shape);
}


void Frog::removeFromLayer() {
	float px = m_sprite->getPositionX();
	float py = m_sprite->getPositionY();
	auto action  = MoveTo::create(0.5, Vec2(px + 30, py - 300));
	auto move_ease_in = EaseBackIn::create(action->clone());
	m_sprite->runAction(move_ease_in);
}


