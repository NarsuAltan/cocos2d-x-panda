#pragma once

#include "cocos2d.h"

class Statistics;
class GameOverLayer : public cocos2d::LayerColor
{
public:
	static GameOverLayer* create(Statistics* statistics);

	virtual bool init(Statistics* statistics);

	void update(float delta);

	void onRestart(Ref* pSender);

	void callback1();

private:
	Statistics* m_statistics;
	cocos2d::Sprite* m_board;
	cocos2d::LabelTTF* m_labelCoin;
	cocos2d::LabelTTF* m_labelKill;
	cocos2d::LabelTTF* m_labelDistance;
	cocos2d::LabelTTF* m_labelScore;
	cocos2d::Menu* m_restartBtn;
	int m_score;
};
