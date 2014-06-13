#include "Fish.h"
#include  "StaticData.h"
USING_NS_CC;
enum{
	k_Action_Animate = 0,
	k_Action_MoveTo
};
Fish* Fish::create(FishType type){
	Fish* fish = new Fish();
	fish->init(type);
	fish->autorelease();
	return fish;
}

bool Fish::init(FishType type){
	_type = type;
	CCString* animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation"),type);
	//从缓存取动画
	CCAnimation* fishAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(animationName->getCString());
	//使用Animation让动画动起来
	CCAnimate* fishAnimate = CCAnimate::create(fishAnimation);
	fishAnimate->setTag(k_Action_Animate);
	//创建精灵
	_fishSprite = CCSprite::create();
	//向节点添加精灵
	this->addChild(_fishSprite);
	_fishSprite->runAction(CCRepeatForever::create(fishAnimate));
	return true;
}

CCRect Fish::getCollisionArea()
{
	CCAssert(this->getParent(), "You Should Call This After Add it as a child");
	CCPoint origin = this->getParent()->convertToWorldSpace(this->getPosition());
	CCSize size = _fishSprite->getContentSize();
	return CCRectMake(origin.x - size.width*0.5, origin.y - size.height*0.5, size.width, size.height);
}

//被捕获
void Fish::beCaught()
{
	//停止移动
	this->stopActionByTag(k_Action_MoveTo);
	CCDelayTime* delayTime = CCDelayTime::create(1.0);
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Fish::beCaught_CallFunc));
	CCFiniteTimeAction* seq = CCSequence::create(delayTime, callFunc, NULL);

	CCBlink* blink = CCBlink::create(1.0, 8);//闪烁特效 1秒 8次
	CCFiniteTimeAction *spawn = CCSpawn::create(seq, blink, NULL);
	this->runAction(spawn);
}

//从父节点移除
void Fish::beCaught_CallFunc()
{
	this->getParent()->removeChild(this, false);
}

void Fish::moveTo(CCPoint destination)
{
	CCPoint start = this->getParent()->convertToWorldSpace(this->getPosition());
	//随机速度
	float speed = ccpDistance(destination, start) / ((CCRANDOM_0_1() *100)+100);
	CCMoveTo* moveTo = CCMoveTo::create(speed, destination);
	CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(Fish::moveEnd));

	CCFiniteTimeAction* seq = CCSequence::create(moveTo, callfunc, NULL);
	seq->setTag(k_Action_MoveTo);
	this->runAction(seq);
}

void Fish::reset()
{
	this->setRotation(0);
	this->setVisible(true);
}

//移动结束
void Fish::moveEnd()
{
	//游出屏幕移除
	this->getParent()->removeChild(this, false);
}
