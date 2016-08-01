#pragma once

#include "cocos2d.h"

class GameLayer;
class HubLayer;
class Statistics;
class GameBackgroundLayer;
class GameScene : public cocos2d::Scene
{
public:
	~GameScene();

	virtual void onEnter();

	void update(float delta);

	CREATE_FUNC(GameScene);

	GameLayer* getLayer() { return m_gameLayer; }

	void setBeAte(bool flag) { m_beAte = flag; }

protected:

	cocos2d::Layer* m_controlLayer;
	HubLayer*		m_hubLayer;
	GameLayer*		m_gameLayer;
	GameBackgroundLayer*	m_farBgLayer;
	GameBackgroundLayer*	m_nearBgLayer;
	Statistics* m_statistics;
	bool	m_gameover;
	bool	m_beAte;
};
