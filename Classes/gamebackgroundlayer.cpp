#include "gamebackgroundlayer.h"
#include "headers.h"

USING_NS_CC;
USING_NS_CC_EXT;

GameBackgroundLayer* GameBackgroundLayer::create(std::string res)
{ 
	GameBackgroundLayer *pRet = new(std::nothrow) GameBackgroundLayer(); 
	if (pRet && pRet->init(res)) 
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


bool GameBackgroundLayer::init(std::string res)
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	m_nearBg = tileBg(res);
    return true;
}

bool GameBackgroundLayer::refresh(float eyeX, float eyeY)
{
	int newNearBgIndex = int(eyeX / m_nearBg[0]->getContentSize().width);
	if (m_nearBgIndex == newNearBgIndex) {
		return false;
	}
	m_nearBg[(newNearBgIndex + m_nearBg.size() - 1) % m_nearBg.size()]->setPositionX(m_nearBg[0]->getContentSize().width * (newNearBgIndex + m_nearBg.size() - 1));
	m_nearBgIndex = newNearBgIndex;

	return true;
}

Sprite* GameBackgroundLayer::createBg(std::string res, Vec2 pos)
{
	auto bg = Sprite::create(res);
	bg->setPosition(pos);
	bg->setAnchorPoint(Vec2::ZERO);
	return bg;
}

std::vector<Sprite*> GameBackgroundLayer::tileBg(std::string res)
{
	auto director = Director::getInstance();
	Size winSize = director->getWinSize();
	float doubleWinWidth = 2 * winSize.width;
	std::vector<Sprite*> tiles;
	float remainWidth = doubleWinWidth;

	do 
	{
		Sprite* nearBg = createBg(res, Vec2(doubleWinWidth - remainWidth, 0));
		remainWidth -= nearBg->getContentSize().width;
		tiles.push_back(nearBg);
		addChild(nearBg);
	} while (remainWidth > 0);
	if (tiles.size() < 2)
	{
		Sprite* nearBg = createBg(res, Vec2(doubleWinWidth - remainWidth, 0));
		tiles.push_back(nearBg);
		addChild(nearBg);
	}
	return tiles;
}

