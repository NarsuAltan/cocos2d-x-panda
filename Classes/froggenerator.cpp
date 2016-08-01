#include "froggenerator.h"
#include "headers.h"


USING_NS_CC;
USING_NS_CC_EXT;


FrogGenerator::~FrogGenerator()
{
	delete m_frog;
}
// on "init" you need to initialize your instance
bool FrogGenerator::init(cpSpace* space, GameLayer* layer)
{
	m_space = space;
	m_layer = layer;

	m_frog = new Frog();
	m_frog->init(-100, -100);
	m_frog->addToLayer(space, layer);
	return true;
}

void FrogGenerator::addRandomFrog(Platform* platform) {
	if (!platform) return;
	if (platform->getLength() <= 1) {
		return;
	}
	m_px = platform->getLastX() - int(CCRANDOM_0_1() * 180 + 80);
	m_py = platform->getY() + 60;
	if (m_layer->getPlayer()->getSprite()->getPositionX() - m_frog->getX() > 250) {
		cpBodySetPosition(m_frog->getBody(), cpv(m_px, m_py));
	}
}

void FrogGenerator::update(float delta)
{

}
