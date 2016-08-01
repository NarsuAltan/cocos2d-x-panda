#pragma once

#include "cocos2d.h"



class GameBackgroundLayer : public cocos2d::Layer
{
public:
	static GameBackgroundLayer* create(std::string res);

	virtual bool init(std::string res);

	bool refresh(float eyeX, float eyeY);

private:
	cocos2d::Sprite* createBg(std::string res, cocos2d::Vec2 pos);

	std::vector<cocos2d::Sprite*> tileBg(std::string res);

private:
	std::vector<cocos2d::Sprite*>	m_nearBg;
	int	m_nearBgIndex;
};
