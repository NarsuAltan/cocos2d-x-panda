#pragma once
#include "cocos2d.h"
#include "chipmunk/chipmunk.h"
#include "extensions/cocos-ext.h"
#include "object.h"

class Platform: public GameObject
{
public:
	~Platform();

	bool init(float x, float y, int length);

	void addToLayer(cpSpace* space, cocos2d::Layer* layer);

	void removeFromLayer();

	float getLastX();

	float getX();

	int getLength();

private:

	float m_width;
	int	m_length;
	float m_speedX;

};
