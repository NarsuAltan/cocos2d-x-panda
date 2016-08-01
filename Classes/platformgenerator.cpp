#include "platformgenerator.h"
#include "headers.h"


USING_NS_CC;
USING_NS_CC_EXT;

PlatformGenerator::~PlatformGenerator()
{
	for (int i = 0; i < m_platformArr.size(); i++)
	{
		delete m_platformArr[i];
	}

}
// on "init" you need to initialize your instance
bool PlatformGenerator::init(cpSpace* space, GameLayer* layer, bool more)
{
	m_space = space;
	m_layer = layer;
	auto director = Director::getInstance();
	Size winSize = director->getWinSize();
	Vec2 pos(winSize.width / 2, winSize.height / 2 - 50);


	Platform* platform = new Platform();
	platform->init(pos.x, pos.y, 2);
	platform->addToLayer(space, layer);
	m_platformArr.push_back(platform);


	return true;
}

Platform* PlatformGenerator::generate(float x)
{
	int gap = int(CCRANDOM_0_1() * 200 + 100); //100~200
	int height = int(CCRANDOM_0_1() * 150 + 100); //100~300
	int block = int(CCRANDOM_0_1() * 4);

	Platform* platform = new Platform();
	platform->init(x + gap, height, block);
	platform->addToLayer(m_space, m_layer);
	m_platformArr.push_back(platform);

	return platform;
}

Platform* PlatformGenerator::update(float delta)
{

	unsigned i = 0;
	auto director = Director::getInstance();
	Size winSize = director->getWinSize();

	for (i = 0; i < m_platformArr.size(); i++) {
		if (m_layer->getEyeX() - m_platformArr[i]->getLastX() < 0) {
			break;
		}
	}

	if (i > 1)
	{
		for (int j = 0; j < i - 1; j++)
		{
			m_platformArr[j]->removeFromLayer();
			delete m_platformArr[j];
		}
		m_platformArr.erase(m_platformArr.begin(), m_platformArr.begin() + i - 1);
	}
		

	int mostX = m_platformArr[m_platformArr.size() - 1]->getLastX();
	if (mostX < m_layer->getEyeX() + winSize.width) {
		return generate(mostX);
	}
	return NULL;
}
