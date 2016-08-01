#pragma once
#include "cocos2d.h"
#include "chipmunk/chipmunk.h"
#include "extensions/cocos-ext.h"
#include "object.h"

class Player: public GameObject
{
public:
	~Player();

	bool init(float x, float y);

	void addToLayer(cpSpace* space, cocos2d::Layer* layer);

	void update(float delta);

	void jump();

	void doubleJump();

	void speedUp();

	float getX();

	void died();


	bool inStatus(std::string status);

	bool isDoubleJumpAlready();

	cpVect getVelocity();

private:

	// animations.
	cocos2d::Action*	m_runningAction;
	cocos2d::Action*	m_jumpUpAction;
	cocos2d::Action*	m_jumpDownAction;

	// the status.
	std::string m_status;

	// player speed.
	float m_runningSpeed;
	float m_x;
	float m_y;
	float m_speedX;

	bool m_isJump;
	bool m_doubleJumpAlready;
};
