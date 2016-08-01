#include "gamescene.h"
#include "chipmunk/chipmunk.h"
#include "extensions/cocos-ext.h"
#include "headers.h"

USING_NS_CC;
USING_NS_CC_EXT;

GameScene::~GameScene()
{
	delete m_statistics;

}
void GameScene::onEnter()
{
	m_gameover = false;
	m_beAte = false;

	Scene::onEnter();
	m_statistics = new Statistics;
	
	m_controlLayer = Layer::create();
	m_controlLayer->addChild(m_gameLayer = GameLayer::create(m_statistics), 1);

	addChild(m_farBgLayer = GameBackgroundLayer::create("res/far-bg.png"));
	addChild(m_nearBgLayer = GameBackgroundLayer::create("res/near-bg.png"));
	addChild(m_controlLayer, 0);

	m_hubLayer = HubLayer::create(m_statistics);
	addChild(m_hubLayer, 1);

	scheduleUpdate();
}

void GameScene::update(float delta)
{	
	if (!m_gameover)
	{
		float eyeX = m_gameLayer->getEyeX(), eyeY = std::max(m_gameLayer->getEyeY(), 0.0f);

		if (m_gameLayer->getPlayer()->getSprite()->getPositionY() < 800) {
			m_controlLayer->setPosition(Vec2(-eyeX, -eyeY / 2.6));
		}
		else {
			m_controlLayer->setPosition(Vec2(-eyeX, -eyeY));
		}

		m_nearBgLayer->refresh(eyeX / 2, eyeY);
		m_nearBgLayer->setPosition(Vec2(-eyeX / 2, -eyeY / 5));

		m_farBgLayer->refresh(eyeX / 3, eyeY);
		m_farBgLayer->setPosition(Vec2(-eyeX / 3, -eyeY / 10));


		if ((m_gameLayer->getPlayer()->getSprite()->getPositionY() < -100 || m_beAte) && !m_gameover) {
			m_gameLayer->getPlayer()->died();
			addChild(GameOverLayer::create(m_statistics), 2);
			m_gameover = true;
		}
		cpVect vel = m_gameLayer->getPlayer()->getVelocity();
		if (vel.x < 1) {
			m_beAte = true;
		}

		m_statistics->setMeter(m_gameLayer->getPlayer()->getSprite()->getPositionX() / 50);
	}
}



