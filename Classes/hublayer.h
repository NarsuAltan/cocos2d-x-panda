#pragma once

#include "cocos2d.h"

class Statistics;
class HubLayer : public cocos2d::Layer
{
public:
	static HubLayer* create(Statistics* statistics);

	virtual bool init(Statistics* statistics);

	void update(float delta);

private:
	Statistics* m_statistics;
	cocos2d::LabelTTF*	m_labelCoin;
	cocos2d::LabelTTF*	m_labelRun;
};
