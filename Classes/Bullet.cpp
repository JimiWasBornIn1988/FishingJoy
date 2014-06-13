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
	//���ת���ͽǶȵļ���
	CCPoint startInNodeSpace = CCPointZero;
	CCPoint startInWorldSpace = this->getParent()->convertToWorldSpace(startInNodeSpace);
	CCPoint targetInNodeSpace = this->getParent()->convertToNodeSpace(targetInWorldSpace);
	//���㻡��
	float angle = ccpAngleSigned(ccpSub(targetInWorldSpace, startInWorldSpace), CCPointMake(0, 1));

	this->setRotation(CC_RADIANS_TO_DEGREES(angle));//����תΪ�Ƕ�
	this->setPosition(startInNodeSpace);
	this->setVisible(true);//���ÿɼ�

	//�����ӵ��̶��ķ����ٶ�
	float speed = 300.0f;
	float duration = ccpDistance(startInNodeSpace, targetInNodeSpace) / speed;//�������ʱ��
	CCMoveTo* moveTo = CCMoveTo::create(duration, targetInNodeSpace);//�����Զ���
	CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(Bullet::end));//�ص�����

	//��������
	CCFiniteTimeAction* seq = CCSequence::create(moveTo, callFunc, NULL);
	seq->setTag(k_Bullet_Action);
	this->runAction(seq);
}

//��������
void Bullet::end()
{
	this->stopActionByTag(k_Bullet_Action);
	this->setVisible(false);
}

//��ȡ��ײ��
CCPoint Bullet::getCollisionPoint()
{
	return this->getParent()->convertToWorldSpace(this->getPosition());
}
