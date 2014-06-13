#include "BackgroundLayer.h"
#include "StaticData.h"
USING_NS_CC;

bool BackgroundLayer::init(){
	if (CCLayer::init()){
		//��ȡ��ͼ��С
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		//�����ƴӻ����м���ͼƬ
		CCSprite* background = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("background"));
		background->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.5));
		this->addChild(background);
		return true;
	}
	return false;
}