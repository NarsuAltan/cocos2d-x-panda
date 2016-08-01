#pragma once
#include "cocos2d.h"

class Player;
class Statistics
{
public:
	Statistics();

	int coin() { return m_coins; }

	int meter() { return m_meter; }

	int kill() { return m_kill; }

	void addCoin(int var);

	void addKill(int var);

	void setMeter(int var);

	int score();

	int length();

	void reset(Player* player);

private:
	int m_coins;
	int m_meter;
	int m_kill;
	Player* m_player;
};
