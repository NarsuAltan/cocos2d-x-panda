#pragma once
#include "cocos2d.h"
#include <vector>

class Gold;
class GameLayer;
class Platform;
class GoldGenerator
{
public:
	~GoldGenerator();

	bool init(cpSpace* space, GameLayer* layer);

	void create(int type, Platform* platform);

	void addRandomGold(Platform* platform);

	void update(float delta);

	Gold* findGold(cpShape* shape);

private:
	std::vector<Gold*> m_gold;
	GameLayer*	m_layer;
	cpSpace*	m_space;
	float		m_px;
	float		m_py;
};
