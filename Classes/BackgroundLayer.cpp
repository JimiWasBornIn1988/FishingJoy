#include "BackgroundLayer.h"
#include "StaticData.h"
USING_NS_CC;

bool BackgroundLayer::init(){
	if (CCLayer::init()){
		//获取视图大小
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		//由名称从缓存中加载图片
		CCSprite* background = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("background"));
		background->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.5));
		this->addChild(background);
		return true;
	}
	return false;
}
