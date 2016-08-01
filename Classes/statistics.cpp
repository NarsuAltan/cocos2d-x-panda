#include "statistics.h"
#include "headers.h"

USING_NS_CC;
USING_NS_CC_EXT;

Statistics::Statistics()
{
	m_coins = 0;
	m_meter = 0;
	m_kill = 0;
	m_player = NULL;
}

void Statistics::addCoin(int var)
{
	m_coins += var;
}

void Statistics::addKill(int var)
{
	m_kill += var;
}
void Statistics::setMeter(int var)
{
	m_meter = var;
}

int Statistics::score() {
	return m_coins * 10;
}

int Statistics::length() {
	return int(m_player->getSprite()->getPositionX() / 100);
}

void Statistics::reset(Player* player) {
	m_player = player;
	m_coins = 0;
	m_meter = 0;
	m_kill = 0;
}