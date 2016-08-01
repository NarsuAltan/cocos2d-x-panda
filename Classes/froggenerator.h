#pragma once
#include "cocos2d.h"
#include <vector>

class Frog;
class GameLayer;
class Platform;
class FrogGenerator
{
public:
	~FrogGenerator();

	bool init(cpSpace* space, GameLayer* layer);

	void addRandomFrog(Platform* platform);

	void update(float delta);

	Frog* getFrog() { return m_frog; }


private:
	Frog*		m_frog;
	GameLayer*	m_layer;
	cpSpace*	m_space;
	float		m_px;
	float		m_py;
};
