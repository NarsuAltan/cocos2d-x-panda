#include "goldgenerator.h"
#include "headers.h"


USING_NS_CC;
USING_NS_CC_EXT;

GoldGenerator::~GoldGenerator()
{
	for (int i = 0; i < m_gold.size(); i++)
	{
		delete m_gold[i];
	}
}
// on "init" you need to initialize your instance
bool GoldGenerator::init(cpSpace* space, GameLayer* layer)
{
	m_space = space;
	m_layer = layer;
	m_px = 0;
	m_py = 0;

	for (int i = 0; i < 22; i++) {
		Gold* o = new Gold();
		o->init(-100, -100);
		m_gold.push_back(o);
		o->addToLayer(space, layer);
	}

	return true;
}


void GoldGenerator::create(int type, Platform* platform) {
	float dy = 0;
	switch (type) {
	case 0:   //bridge shape
		{
			float x = m_px + 200;
			float y = m_py + 140;
			float radius = CCRANDOM_0_1() * 6 + 5;

			for (int i = -4; i < 5; i++) {
				x += 60;
				dy = -i*i*radius + 100;
				cpBodySetPosition(m_gold[4 + i]->getBody(), cpv(x, y + dy));
			}
		}

		break;
	case 1:   // rectangle shape
		{
			float x = m_px + 130;
			float y = m_py + 150;

			int k = 0;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 3; j++) {
					cpBodySetPosition(m_gold[k]->getBody(), cpv(x + i * 60, y + j * 60));
					++k;
				}
			}
		}
		break;
	case 2:   //line
		{
			float x = m_px + 130;
			float y = m_py + 130;
			int nums = 6;

			for (int i = 0; i < nums; i++) {
				cpBodySetPosition(m_gold[i]->getBody(), cpv(x + i * 60, y));
			}
		}

		break;
	case 3: //two lines
		{
			float x = m_px + 130;
			float y = m_py + 110;
			int nums = 6;

			int k = 0;
			for (int i = 0; i < nums; i++) {
				for (int j = 0; j < 2; j++) {
					cpBodySetPosition(m_gold[k]->getBody(), cpv(x + i * 60, y + j * 50));
					++k;
				}
			}
		}
		break;
	case 4: //two bridges
		{
			float x = m_px + 200;
			float y = m_py + 140;
			float radius = CCRANDOM_0_1() * 5 + 5;

			for (int i = -4; i < 5; i++) {
				x += 60;
				dy = -i*i*radius + 100;
				//					int gold = new Gold(x, y+dy);
				cpBodySetPosition(m_gold[i + 4]->getBody(), cpv(x, y + dy));


				float dy2 = -i*i*radius + 150;
				//int gold = new Gold(x, y+dy2);
				cpBodySetPosition(m_gold[i + 13]->getBody(), cpv(x, y + dy2));
			}
		}

		break;
	case 5: //triangle shape
		{
			float x = m_px + 220;
			float y = m_py + 130;
			float dx = 0;
			float dy = 0;

			int k = 0;
			for (int i = 0; i < 6; i++) {
				dy = i * 40;
				dx = 25 * i;
				for (int j = 0; j < 6 - i; j++) {
					//int gold = new Gold(x+dx+j*50, y+dy);
					cpBodySetPosition(m_gold[k]->getBody(), cpv(x + dx + j * 50, y + dy));
					++k;
				}
			}
		}

		break;
	case 6: ////prismatic shape
		{
			float x = m_px + 200;
			float y = m_py + 120;
			float offsetLeft = 0.0;
			int k = 0;
			int nums = 0;
			for (int i = 0; i < 7; i++) {
				dy = i * 35;
				if (i < 4) {
					nums = i + 1;
					offsetLeft = (3 - i) * 30;
				}
				else {
					nums = 7 - i;
					offsetLeft = (i - 3) * 30;
				}
				for (int j = 0; j < nums; j++) {
					//						int gold = new Gold(x+ offsetLeft + 60*j, y+dy);
					cpBodySetPosition(m_gold[k]->getBody(), cpv(x + offsetLeft + 60 * j, y + dy));
					++k;
				}
			}
		}
		break;

	default:break;

	}

}

void GoldGenerator::addRandomGold(Platform* platform) {
	if (!platform) return;
	if (platform->getLength() <= 1) {
		return;
	}
	m_px = platform->getX();
	m_py = platform->getY();
	int randType = int(CCRANDOM_0_1() * 7);
	if (m_layer->getPlayer()->getSprite()->getPositionX() - m_gold[0]->getX() > 800) {
		create(randType, platform);
	}
}

void GoldGenerator::update(float delta)
{

}

Gold* GoldGenerator::findGold(cpShape* shape)
{
	for (int i = 0; i < m_gold.size(); i++)
	{
		if (m_gold[i]->getShape() == shape)
		{
			return m_gold[i];
		}
	}
	return NULL;
}