#include "gameopeninglayer.h"
#include "headers.h"

USING_NS_CC;




// on "init" you need to initialize your instance
bool GameOpeningLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/gold.plist");
	cache->addSpriteFramesWithFile("res/platform.plist");
	cache->addSpriteFramesWithFile("res/panda.plist");
	cache->addSpriteFramesWithFile("res/shoes.plist");
	cache->addSpriteFramesWithFile("res/redshoes.plist");
	cache->addSpriteFramesWithFile("res/spring.plist");
	cache->addSpriteFramesWithFile("res/bird.plist");
	cache->addSpriteFramesWithFile("res/enemy.plist");
	cache->addSpriteFramesWithFile("res/magnet.plist");


	auto director = Director::getInstance();
	Size size = director->getWinSize();

	auto bg = Sprite::create("res/open-bg.png");
	bg->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(bg, 0);

	auto team = Sprite::create("res/maxon-team.png");
	team->setPosition(Vec2(size.width / 2, size.height / 2));
	team->setScale(0.4);
	addChild(team, 1);
	team->setOpacity(0);
	auto fadeIn = FadeIn::create(1.0);
	auto fadeOut = FadeOut::create(1.0);
	auto delay = DelayTime::create(1.0f);
	auto seq = Sequence::create(
		fadeIn,
		delay,
		fadeOut,
		nullptr);
	team->runAction(seq);

	return true;
}
