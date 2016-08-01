#pragma once
#include "cocos2d.h"
#include <vector>

class Platform;
class GameLayer;
class PlatformGenerator
{
public:
	~PlatformGenerator();

	bool init(cpSpace* space, GameLayer* layer, bool more = false);

	Platform* generate(float x);

	Platform* update(float delta);



private:
	std::vector<Platform*> m_platformArr;
	GameLayer*	m_layer;
	cpSpace*	m_space;
};
