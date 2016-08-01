#include "splashscene.h"
#include "headers.h"

USING_NS_CC;

void SplashScene::onEnter()
{
	Scene::onEnter();
	auto open = GameOpeningLayer::create();
	addChild(open, 1, 1);

	runAction(Sequence::create(
		DelayTime::create(3.0f),
		CallFunc::create(CC_CALLBACK_0(SplashScene::callback1, this)),
		nullptr));
}

void SplashScene::callback1()
{
	auto director = Director::getInstance();
	director->replaceScene(GameScene::create()); 
}

