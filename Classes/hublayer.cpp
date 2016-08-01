#include "hublayer.h"
#include "chipmunk/chipmunk.h"
#include "headers.h"

USING_NS_CC;
USING_NS_CC_EXT;

HubLayer* HubLayer::create(Statistics* statistics)
{
	HubLayer *pRet = new(std::nothrow) HubLayer();
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


// on "init" you need to initialize your instance
bool HubLayer::init(Statistics* statistics)
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	m_statistics = statistics;

	auto director = Director::getInstance();
	Size winSize = director->getWinSize();

	auto goldbar = Sprite::create("res/ui/gold-bar.png");
	goldbar->setPosition(Vec2(120,winSize.height - 40));
	addChild(goldbar);

	auto energybar = Sprite::create("res/ui/energy-bar.png");
	energybar->setPosition(Vec2(350, winSize.height - 40));
	addChild(energybar);

	auto progress = Sprite::create("res/ui/progress.png");
	progress->setPosition(Vec2(303.5, winSize.height - 40));
	progress->setAnchorPoint(Vec2(0, 0.5));
	progress->setScaleX(0.00001f);
	progress->setScaleY(0.9f);
	addChild(progress);

	char str[100] = { 0 };
	sprintf(str, "%d", m_statistics->score());

	m_labelCoin = LabelTTF::create(str, "Helvetica", 50);
	m_labelCoin->setColor(Color3B(255, 255, 255));// white color
	m_labelCoin->setPosition(Vec2(130, winSize.height - 43));
	m_labelCoin->setScale(0.4f);
	addChild(m_labelCoin);


	// running distance
	auto distance = Sprite::create("res/ui/distance.png");
	distance->setPosition(Vec2(490, winSize.height - 40));
	distance->setAnchorPoint(Vec2(0, 0.5));
	addChild(distance);

	m_labelRun = LabelTTF::create("0m", "Helvetica", 50);
	m_labelRun->setColor(Color3B(255, 255, 255));// white color
	m_labelRun->setPosition(Vec2(605, winSize.height - 43));
	m_labelRun->setScale(0.4f);
	addChild(m_labelRun);




	

	scheduleUpdate();

	return true;
}

void HubLayer::update(float delta)
{
	char str[100] = { 0 };
	sprintf(str, "%d", m_statistics->coin());
	m_labelCoin->setString(str);

	memset(str, 0, 100);
	sprintf(str, "%d m", m_statistics->meter());
	m_labelRun->setString(str);

}
