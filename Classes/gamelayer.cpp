#include "gamelayer.h"
#include "chipmunk/chipmunk.h"
#include "headers.h"

USING_NS_CC;
USING_NS_CC_EXT;


GameLayer* GameLayer::create(Statistics* statistics)
{
	GameLayer *pRet = new(std::nothrow) GameLayer();
	if (pRet && pRet->init(statistics))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}


GameLayer::~GameLayer()
{

	delete m_player;
	delete m_platformGenerator;
	delete m_goldGenerator;
	delete m_frogGenerator;

	// manually Free rogue shapes
	cpShapeFree(m_wallBottom);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	cpSpaceFree(m_space);
#else
	cpHastySpaceFree(m_space);
#endif

}
// on "init" you need to initialize your instance
bool GameLayer::init(Statistics* statistics)
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	initSpace();
	m_statistics = statistics;
	m_playerPosOfScene = Vec2(230, 250);
	//this->addChild(PhysicsDebugNode::create(space), 100);

	auto director = Director::getInstance();
	Size winSize = director->getWinSize();
	Vec2 centerPos = Vec2(winSize.width / 2 - 100, 400);

	
	m_player = new Player;
	m_player->init(centerPos.x, centerPos.y + 50);
	m_player->addToLayer(m_space, this);

	// Register Touch Event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	m_platformGenerator = new PlatformGenerator();
	m_platformGenerator->init(m_space, this);

	m_goldGenerator = new GoldGenerator();
	m_goldGenerator->init(m_space, this);

	m_frogGenerator = new FrogGenerator();
	m_frogGenerator->init(m_space, this);

	scheduleUpdate();

	return true;
}


void GameLayer::update(float delta)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	cpSpaceStep(m_space, delta);
#else
	cpHastySpaceStep(m_space, delta);
#endif

	// update the player.
	m_player->update(delta);

	Platform* platform = m_platformGenerator->update(delta);
	int diffDeg = 0;
	float birdChance = 0;
	float frogChance = 0;

	if (diffDeg == 0) {
		birdChance = 1.7f;
		frogChance = 1.5f;
	}
	else if (diffDeg == 1) {
		birdChance = 1.4f;
		frogChance = 1;
		if (CCRANDOM_0_1() * 2 > 1.8) {
			m_player->speedUp();
		}
	}

	//add gold randomly
	if (platform && CCRANDOM_0_1() * 2 > 1.2) {
		m_goldGenerator->addRandomGold(platform);
	}

	//add frog enemy randomly
	if (platform /*&& CCRANDOM_0_1() * 2 > frogChance*/) {
		m_frogGenerator->addRandomFrog(platform);
	}

}

bool GameLayer::onTouchBegan(Touch* touch, Event* event)
{
	if (m_player->inStatus("running")) {
		m_player->jump();
	}
	else if ((m_player->inStatus("jumpUp") || m_player->inStatus("jumpDown")) && !m_player->isDoubleJumpAlready()) {
		m_player->doubleJump();
	}
	return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event* event)
{

}


void GameLayer::onTouchEnded(Touch* touch, Event* event)
{

}

Player* GameLayer::getPlayer()
{
	return m_player;
}

float GameLayer::getEyeX()
{
	return m_player->getSprite()->getPositionX() - m_playerPosOfScene.x;
}

float GameLayer::getEyeY() 
{
	return m_player->getSprite()->getPositionY() - m_playerPosOfScene.y;
}

bool GameLayer::collisionGold(cpShape *a, cpShape *b)
{
	m_statistics->addCoin(1);
	//remove golds

	Gold* gold = m_goldGenerator->findGold(b);
	if (gold)
	{
		gold->removeFromLayer();
	}
	return true;
}
cpBool _collisionGold(cpArbiter *arb, cpSpace *space, cpDataPointer userData)
{
	GameLayer* gameLayer = (GameLayer*)userData;
	cpShape *a = NULL;
	cpShape *b = NULL;
	cpArbiterGetShapes(arb, &a, &b);

	return gameLayer->collisionGold(a, b);
}

bool GameLayer::collisionFrog(cpShape *a, cpShape *b)
{
	if (m_player->inStatus("jumpDown"))
	{
		m_frogGenerator->getFrog()->removeFromLayer();
		m_statistics->addKill(1);
	}
	else
	{
		GameScene* gameScene = (GameScene*)getParent()->getParent();
		gameScene->setBeAte(true);
	}

	return true;
}
cpBool _collisionFrog(cpArbiter *arb, cpSpace *space, cpDataPointer userData)
{
	GameLayer* gameLayer = (GameLayer*)userData;
	cpShape *a = NULL;
	cpShape *b = NULL;
	cpArbiterGetShapes(arb, &a, &b);

	return gameLayer->collisionFrog(a, b);
}



void GameLayer::initSpace()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	m_space = cpSpaceNew();
#else
	m_space = cpHastySpaceNew();
	cpHastySpaceSetThreads(m_space, 0);
#endif

	cpSpaceSetGravity(m_space, cpv(0, -1500));

	// bottom
	m_wallBottom = cpSegmentShapeNew(cpSpaceGetStaticBody(m_space),
		cpv(0, -1000),
		cpv(float(429496729), -1000), 0.0f);


	//
	cpShapeSetCollisionType(m_wallBottom, SpriteTag::ground);
	cpSpaceAddShape(m_space, m_wallBottom);

	cpCollisionType     typeA = SpriteTag::player;
	cpCollisionType     typeB = SpriteTag::gold;
	cpCollisionHandler* cp_collision_handler = cpSpaceAddCollisionHandler(m_space, typeA, typeB);
	cp_collision_handler->userData = this;
	cp_collision_handler->beginFunc = _collisionGold;


	typeA = SpriteTag::player;
	typeB = SpriteTag::frog;
	cp_collision_handler = cpSpaceAddCollisionHandler(m_space, typeA, typeB);
	cp_collision_handler->userData = this;
	cp_collision_handler->beginFunc = _collisionFrog;

}