#pragma once
#include "cocos2d.h"
#include "chipmunk/chipmunk.h"
#include "extensions/cocos-ext.h"
#include "object.h"

class Gold : public GameObject
{
public:
	~Gold();

	bool init(float posX, float posY);

	void addToLayer(cpSpace* space, cocos2d::Layer* layer);

	void removeFromLayer();


private:
	cocos2d::Action*		m_rotatingAction;

	float m_x;
	float m_y;

};
