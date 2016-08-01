#pragma once

#include "cocos2d.h"

class GameObject;
class Player;
class PlatformGenerator;
class GoldGenerator;
class FrogGenerator;
class Statistics;
class GameLayer : public cocos2d::Layer
{
public:
	~GameLayer();
	static GameLayer* create(Statistics* statistics);

	virtual bool init(Statistics* statistics);

	void update(float delta);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	Player* getPlayer();
	float getEyeX();
	float getEyeY();

	bool collisionGold(cpShape *a, cpShape *b);

	bool collisionFrog(cpShape *a, cpShape *b);
private:
	void initSpace();
private:
	cpSpace*		m_space;
	cpShape*		m_wallBottom;
	Player*			m_player;
	cocos2d::Vec2		m_playerPosOfScene;


	PlatformGenerator*	m_platformGenerator;
	GoldGenerator*	m_goldGenerator;
	FrogGenerator* m_frogGenerator;


	Statistics* m_statistics;
};
