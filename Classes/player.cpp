#include "player.h"
#include "headers.h"

USING_NS_CC;
USING_NS_CC_EXT;


Player::~Player()
{
	m_runningAction->release();
	m_jumpUpAction->release();
	m_jumpDownAction->release();

	cpSpaceRemoveBody(m_space, m_body);
}
// on "init" you need to initialize your instance
bool Player::init(float x, float y)
{
	m_x = x;
	m_y = y;
	m_speedX = 0;
	m_status = "running";
	m_runningSpeed = 2500;
	m_doubleJumpAlready = false;
	m_spriteSheet = SpriteBatchNode::create("res/panda.png");

	char str[100] = { 0 };
	auto cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames(8);
	for (int i = 0; i < 8; i++)
	{
		sprintf(str, "panda_run_%02d.png", i + 1);
		animFrames.pushBack(cache->getSpriteFrameByName(str));
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	m_runningAction = RepeatForever::create(Animate::create(animation));
	m_runningAction->retain();

	animFrames.clear();
	for (int i = 0; i < 8; i++)
	{
		sprintf(str, "panda_jump_%02d.png", i + 1);
		animFrames.pushBack(cache->getSpriteFrameByName(str));
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.08f);
	m_jumpUpAction = RepeatForever::create(Animate::create(animation));
	m_jumpUpAction->retain();

	animFrames.clear();
	for (int i = 0; i < 8; i++)
	{
		sprintf(str, "panda_roll_%02d.png", i + 1);
		animFrames.pushBack(cache->getSpriteFrameByName(str));
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.08f);
	m_jumpDownAction = RepeatForever::create(Animate::create(animation));
	m_jumpDownAction->retain();


	m_sprite = PhysicsSprite::createWithSpriteFrameName("panda_run_01.png");
	m_spriteSheet->addChild(m_sprite);

	Size contentSize = m_sprite->getContentSize();


	m_body = cpBodyNew(5, cpMomentForBox(PHYSICS_INFINITY, contentSize.width, contentSize.height));
	cpBodySetPosition(m_body, cpv(x, y));
	cpBodyApplyImpulseAtLocalPoint(m_body, cpv(m_runningSpeed, 0), cpv(0, 0));
	m_sprite->setCPBody(m_body);

	m_shape = cpBoxShapeNew(m_body, contentSize.width - 14, contentSize.height - 10, 0);
	cpShapeSetCollisionType(m_shape, SpriteTag::player);
	cpShapeSetElasticity(m_shape, 1.0f);

	m_sprite->runAction(m_runningAction);


	return true;
}

void Player::addToLayer(cpSpace* space, cocos2d::Layer* layer)
{
	m_space = space;
	m_layer = layer;
	m_layer->addChild(m_spriteSheet);

	cpSpaceAddBody(m_space, m_body);
	cpSpaceAddShape(m_space, m_shape);
}

void Player::update(float delta)
{
	cpVect vel = getVelocity();
	if (inStatus("jumpUp")) {
		if (vel.y < 0.1) {
			m_status = "jumpDown";
			m_sprite->stopAllActions();
			m_sprite->runAction(m_jumpDownAction);
		}
	}
	else if (inStatus("jumpDown")) {
		if (vel.y == 0) {
			m_isJump = false;
			m_status = "running";
			m_doubleJumpAlready = false;
			m_sprite->stopAllActions();
			m_sprite->runAction(m_runningAction);
		}
	}
}


void Player::jump()
{
	if (inStatus("running"))
	{
		cpBodyApplyImpulseAtLocalPoint(m_body, cpv(0, 4000), cpv(0, 0));
		m_status = "jumpUp";
		m_sprite->stopAllActions();
		m_sprite->runAction(m_jumpUpAction);
	}
}

void Player::doubleJump()
{
	if (inStatus("jumpUp"))
	{
		cpBodyApplyImpulseAtLocalPoint(m_body, cpv(0, 2500), cpv(0, 0));
		m_doubleJumpAlready = true;
		m_sprite->stopAllActions();
		m_sprite->runAction(m_jumpUpAction);
	}
	else if(inStatus("jumpDown"))
	{
		cpBodyApplyImpulseAtLocalPoint(m_body, cpv(0, 4000), cpv(0, 0));
		m_doubleJumpAlready = true;
		m_sprite->stopAllActions();
		m_sprite->runAction(m_jumpUpAction);
	}
}


void Player::speedUp()
{
	m_speedX = 5;
	cpBodyApplyImpulseAtLocalPoint(m_body, cpv(m_speedX, 0), cpv(0, 0));
}

void Player::died()
{
	cpShapeSetSensor(m_shape, true);
	cpBodyApplyImpulseAtLocalPoint(m_body, cpv(0, 4000), cpv(0, 0));
	cpBodyApplyImpulseAtLocalPoint(m_body, cpv(-m_runningSpeed, 0), cpv(0, 0));
}

bool Player::inStatus(std::string status)
{
	return m_status == status;
}
bool Player::isDoubleJumpAlready()
{
	return m_doubleJumpAlready;
}

cpVect Player::getVelocity()
{
	return cpBodyGetVelocity(m_body);
}
