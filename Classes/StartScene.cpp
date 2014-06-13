#include "StartScene.h"
#include "GameScene.h"
#include "PersonalAudioEngine.h"
#include "StaticData.h"
#include "Fish.h"
#include "FishingJoyData.h"
USING_NS_CC;
using namespace CocosDenshion;
CCScene* StartLayer::scene()
{
	CCScene* scene = CCScene::create();
	StartLayer* layer = StartLayer::create();
	scene->addChild(layer);
	return scene;
}
bool StartLayer::init()
{
	if (CCLayer::init()){
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCSprite* background = CCSprite::create(STATIC_DATA_STRING("background"));
		background->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.5));
		this->addChild(background);

		CCSprite* title = CCSprite::create(STATIC_DATA_STRING("title"));
		title->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.7));
		this->addChild(title);

		if (CCDirector::sharedDirector()->getTotalFrames() < 10){//调度器开始后的帧数小于10
			//异步加载图片资源
			CCTextureCache::sharedTextureCache()->addImageAsync(STATIC_DATA_STRING("fishingjoy_texture"), this, callfuncO_selector(StartLayer::loading));
			//加载进度条背景
			CCSprite* progressBg = CCSprite::create(STATIC_DATA_STRING("progress_bg"));
			_progressFg = CCLabelTTF::create("0/100", "Thonburi", 16);
			_progressFg->setColor(ccc3(0, 0, 0));
			//加载进度条
			_progressBar = ProgressBar::create(this, CCSprite::create(STATIC_DATA_STRING("progress_bar")));
			_progressBar->setBackground(progressBg);
			_progressBar->setForeground(_progressFg);
			_progressBar->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.5));
			_progressBar->setSpeed(100.0);
			this->addChild(_progressBar);
			//初始音频和数据
			this->audioAndUserDataInit();
		}
		else{
			this->initializationCompleted();
		}

		return true;
	}
	return false;
}
void StartLayer::audioAndUserDataInit()
{
	//初始化用户数据
	FishingJoyData::sharedFishingJoyData();
	//初始化音乐引擎
	PersonalAudioEngine::sharedEngine();
}
void StartLayer::loading(CCObject* pObj)
{
	_progressBar->progressTo(100.0);
}
void StartLayer::transition(CCObject* pSender)
{
	CCScene* scene = CCTransitionFadeDown::create(1.0f, GameScene::create());
	CCDirector::sharedDirector()->replaceScene(scene);
}
void StartLayer::cacheInit()
{
	//精灵框帧缓存
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fishingjoy_resource.plist");
	int frameCount = STATIC_DATA_INT("fish_frame_count");
	for (int type = k_Fish_Type_Red; type < k_Fish_Type_Count; type++) {
		CCArray* spriteFrames = CCArray::createWithCapacity(frameCount);//用初始容量创建
		for (int i = 0; i < frameCount; i++){
			CCString* filename = CCString::createWithFormat(STATIC_DATA_STRING("fish_frame_name_format"), type, i);//根据格式生成字符串：格式 fish_%d_%d.png
			CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());//从缓存读取框帧
			spriteFrames->addObject(spriteFrame);
		}
		//根据框帧创建动画
		CCAnimation* fishAnimation = CCAnimation::createWithSpriteFrames(spriteFrames);
		fishAnimation->setDelayPerUnit(STATIC_DATA_FLOAT("fish_frame_delay"));
		CCString* animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation"), type);
		CCAnimationCache::sharedAnimationCache()->addAnimation(fishAnimation, animationName->getCString());
	}
}

//初始化完成
void StartLayer::initializationCompleted()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemSprite* start = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("start_normal")), CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("start_selected")), this, menu_selector(StartLayer::transition));
	CCMenu* menu = CCMenu::create(start, NULL);
	menu->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.4));

	this->removeChild(_progressBar, true);
	this->addChild(menu);
	PersonalAudioEngine::sharedEngine()->playBackgroundMusic(STATIC_DATA_STRING("bg_music"));
}
void StartLayer::loadingFinished()
{
	this->cacheInit();
	this->initializationCompleted();
}
void StartLayer::progressPercentageSetter(float percentage)
{
	CCString* str = CCString::createWithFormat("%d/100", (int)percentage);
	_progressFg->setString(str->getCString());
}