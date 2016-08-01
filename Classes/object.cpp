#include "object.h"
#include "headers.h"

USING_NS_CC;


GameObject::~GameObject()
{
	cpSpaceRemoveShape(m_space, m_shape);
	cpShapeFree(m_shape);
	cpBodyFree(m_body);
}