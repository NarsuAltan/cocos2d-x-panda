#include "gameoverlayer.h"
#include "chipmunk/chipmunk.h"
#include "headers.h"

USING_NS_CC;
USING_NS_CC_EXT;

GameOverLayer * GameOverLayer::create(Statistics* statistics)
{
	GameOverLayer * layer = new (std::nothrow) GameOverLayer();
	if (layer && layer->init(statistics))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

// on "init" you need to initialize your instance
bool GameOverLayer::init(Statistics* statistics)
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 80)))
	{
		return false;
	}
	m_statistics = statistics;

	auto director = Director::getInstance();
	Size winSize = director->getWinSize();

	
	//score m_board
	m_board = Sprite::create("res/ui/score-board.png");
	m_board->setPosition(Vec2(winSize.width + 100, winSize.height / 2));
	m_board->setScale(0.7f);
	addChild(m_board, 0);
	auto actionTo = MoveTo::create(0.7f, Vec2(winSize.width / 2, winSize.height / 2));
	auto move_ease = EaseBounceOut::create(actionTo->clone());
	m_board->runAction(move_ease);
	//		menu.runAction(actionTo1);

	m_labelCoin = LabelTTF::create("0", "Helvetica", 35);
	m_labelCoin->setColor(Color3B(67, 144, 67));
	m_labelCoin->setPosition(Vec2(winSize.width + 100, winSize.height / 2 + 25));
	actionTo = MoveTo::create(0.7f, Vec2(winSize.width / 2 + 90, winSize.height / 2 + 25));
	move_ease = EaseBounceOut::create(actionTo->clone());
	m_labelCoin->runAction(move_ease);
	addChild(m_labelCoin);

	m_labelKill = LabelTTF::create("0", "Helvetica", 35);
	m_labelKill->setColor(Color3B(67, 144, 67));
	m_labelKill->setPosition(Vec2(winSize.width + 100, winSize.height / 2 + 85));
	actionTo = MoveTo::create(0.7f, Vec2(winSize.width / 2 + 90, winSize.height / 2 + 85));
	move_ease = EaseBounceOut::create(actionTo->clone());	
	m_labelKill->runAction(move_ease);
	addChild(m_labelKill);

	m_labelDistance = LabelTTF::create("0", "Helvetica", 35);
	m_labelDistance->setColor(Color3B(67, 144, 67));
	m_labelDistance->setPosition(Vec2(winSize.width + 100, winSize.height / 2 - 35));
	actionTo = MoveTo::create(0.7f, Vec2(winSize.width / 2 + 90, winSize.height / 2 - 35));
	move_ease = EaseBounceOut::create(actionTo->clone());
	m_labelDistance->runAction(move_ease);
	addChild(m_labelDistance);

	m_score = m_statistics->kill() * 30 + m_statistics->coin() * 10 + m_statistics->meter();

	m_labelScore = LabelTTF::create("0", "Helvetica", 35);
	m_labelScore->setColor(Color3B(158, 98, 22));
	m_labelScore->setPosition(Vec2(winSize.width + 100, winSize.height / 2 - 95));
	actionTo = MoveTo::create(0.7f, Vec2(winSize.width / 2 + 90, winSize.height / 2 - 95));
	move_ease = EaseBounceOut::create(actionTo->clone());
	m_labelScore->runAction(move_ease);
	addChild(m_labelScore);

	m_restartBtn = Menu::create(MenuItemSprite::create(
		Sprite::create("res/ui/reload.png"),
		Sprite::create("res/ui/reload.png"),
		CC_CALLBACK_1(GameOverLayer::onRestart, this)), nullptr);
	m_restartBtn->setPosition(Vec2(winSize.width + 100, 60));
	m_restartBtn->setAnchorPoint(Vec2(0, 0));
	m_restartBtn->setPosition(Vec2(winSize.width + 100, winSize.height / 2 - 165));
	m_restartBtn->setScale(0.8);
	actionTo = MoveTo::create(0.7f, Vec2(winSize.width / 2, winSize.height / 2 - 165));
	move_ease = EaseBounceOut::create(actionTo->clone());
	m_restartBtn->runAction(move_ease);
	addChild(m_restartBtn, 1);


	char str[100] = { 0 };
	sprintf(str, "%d", m_statistics->coin());
	m_labelCoin->setString(str);

	sprintf(str, "%d", m_statistics->kill());
	m_labelKill->setString(str);

	sprintf(str, "%d", m_statistics->meter());
	m_labelDistance->setString(str);

	sprintf(str, "%d", m_score);
	m_labelScore->setString(str);


	scheduleUpdate();

	return true;
}

void GameOverLayer::update(float delta)
{

}

void GameOverLayer::onRestart(Ref* pSender)
{
	auto director = Director::getInstance();
	Size winSize = director->getWinSize();

	auto action = EaseElasticInOut::create(MoveTo::create(0.7, Vec2(-300, winSize.height / 2))->clone(), 0.45f);
	m_board->runAction(action);

	m_restartBtn->runAction(Sequence::create(
		EaseElasticInOut::create(MoveTo::create(0.7, Vec2(-300, winSize.height / 2 - 165))->clone(), 0.45f),
		CallFunc::create(CC_CALLBACK_0(GameOverLayer::callback1, this)), nullptr));

	


	//label out
	m_labelCoin->runAction(EaseElasticInOut::create(MoveTo::create(0.7, Vec2(-300, winSize.height / 2 + 25))->clone(), 0.45f));

	m_labelKill->runAction(EaseElasticInOut::create(MoveTo::create(0.7, Vec2(-300, winSize.height / 2 + 85))->clone(), 0.45f));

	m_labelDistance->runAction(EaseElasticInOut::create(MoveTo::create(0.7, Vec2(-300, winSize.height / 2 - 35))->clone(), 0.45f));

	m_labelScore->runAction(EaseElasticInOut::create(MoveTo::create(0.7, Vec2(-300, winSize.height / 2 - 95))->clone(), 0.45f));
}

void GameOverLayer::callback1()
{
	auto director = Director::getInstance();
	director->replaceScene(GameScene::create());
}
