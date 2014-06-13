#include "Bullet.h"
#include "StaticData.h"
USING_NS_CC;
enum{
	k_Bullet_Action = 0
};
bool Bullet::init(){
	_bulletSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("bullet"));
	_bulletSprite->setAnchorPoint(CCPointMake(0.5, 1.0));
	this->addChild(_bulletSprite);
	return true;
}

void Bullet::flyTo(CCPoint targetInWorldSpace)
{
	//点的转换和角度的计算
	CCPoint startInNodeSpace = CCPointZero;
	CCPoint startInWorldSpace = this->getParent()->convertToWorldSpace(startInNodeSpace);
	CCPoint targetInNodeSpace = this->getParent()->convertToNodeSpace(targetInWorldSpace);
	//计算弧度
	float angle = ccpAngleSigned(ccpSub(targetInWorldSpace, startInWorldSpace), CCPointMake(0, 1));

	this->setRotation(CC_RADIANS_TO_DEGREES(angle));//弧度转为角度
	this->setPosition(startInNodeSpace);
	this->setVisible(true);//设置可见

	//设置子弹固定的飞行速度
	float speed = 300.0f;
	float duration = ccpDistance(startInNodeSpace, targetInNodeSpace) / speed;//计算持续时间
	CCMoveTo* moveTo = CCMoveTo::create(duration, targetInNodeSpace);//持续性动作
	CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(Bullet::end));//回调函数

	//做出动作
	CCFiniteTimeAction* seq = CCSequence::create(moveTo, callFunc, NULL);
	seq->setTag(k_Bullet_Action);
	this->runAction(seq);
}

//结束动作
void Bullet::end()
{
	this->stopActionByTag(k_Bullet_Action);
	this->setVisible(false);
}

//获取碰撞点
CCPoint Bullet::getCollisionPoint()
{
	return this->getParent()->convertToWorldSpace(this->getPosition());
}
