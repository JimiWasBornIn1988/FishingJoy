#include "GameScene.h"
#include "FishingJoyData.h"
#include "StaticData.h"
#include "PersonalAudioEngine.h"
#include "StartScene.h"
USING_NS_CC;

void GameScene::onEnterTransitionDidFinish()
{
	CCScene::onEnterTransitionDidFinish();
	//进入场景后播放音乐
	PersonalAudioEngine::sharedEngine()->playBackgroundMusic(STATIC_DATA_STRING("bg_music"), true);
}

bool GameScene::init()
{
	if (CCScene::init()){
		//背景层
		_backgroundLayer = BackgroundLayer::create();
		this->addChild(_backgroundLayer);
		//鱼群层
		_fishLayer = FishLayer::create();
		this->addChild(_fishLayer);
		//炮台层
		_cannonLayer = CannonLayer::create();
		this->addChild(_cannonLayer);
		//面板层
		_panelLayer = PanelLayer::create();
		this->addChild(_panelLayer);
		//菜单层
		_menuLayer = MenuLayer::create();
		CC_SAFE_RETAIN(_menuLayer);
        //触发层
		_touchLayer = TouchLayer::create();
		this->addChild(_touchLayer);
		//设置金币显示
		_panelLayer->getGoldCounterLayer()->setNumber(FishingJoyData::sharedFishingJoyData()->getGold());
		//设置音乐和音效音量
		_menuLayer->setSoundAndMusicVolume(FishingJoyData::sharedFishingJoyData()->getSoundVolume(), FishingJoyData::sharedFishingJoyData()->getMusicVolume());

		//增加一个监听
		this->scheduleUpdate();

		return true;
	}
	return false;
}

void GameScene::pause()
{
	_panelLayer->setMenuTouchEnabled(false);
	PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
	PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("sound_button"));
	this->operateAllSchedulerAndActions(this, k_Operate_Pause);
	_touchLayer->setTouchEnabled(false);
	this->addChild(_menuLayer);
}
void GameScene::resume()
{
	_panelLayer->setMenuTouchEnabled(true);
	this->operateAllSchedulerAndActions(this, k_Operate_Resume);
	PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
	this->removeChild(_menuLayer, false);
	_touchLayer->setTouchEnabled(true);
}

void GameScene::sound()
{
	bool flag = FishingJoyData::sharedFishingJoyData()->getSoundVolume() > 0;
	CCLog("GameScene::flag:%d", flag);
	PersonalAudioEngine::sharedEngine()->setEffectsVolume(!flag);
}

void GameScene::music()
{
	bool flag = FishingJoyData::sharedFishingJoyData()->getMusicVolume() > 0;
	CCLog("GameScene::flag:%d", flag);

	PersonalAudioEngine::sharedEngine()->setBackgroundMusicVolume(!flag);
}

void GameScene::reset()
{
}

void GameScene::transToMainMenu()
{
	//跳转场景  
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1, StartLayer::scene()));
}

GameScene::~GameScene()
{
	CC_SAFE_RELEASE(_menuLayer);
}

void GameScene::cannonAimAt(CCPoint target){
	_cannonLayer->aimAt(target);
}

void GameScene::cannonShootTo(CCPoint target){
	int type = _cannonLayer->getWeapon()->getCannon()->getType();
	int cost = (type + 1) * 1;
	int currentGold = FishingJoyData::sharedFishingJoyData()->getGold();
	if (currentGold >= cost && _cannonLayer->shootTo(target)){
		PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("sound_shot"));
		this->alterGold(-cost);
	}
}

//监听函数 重写CCNode的update函数
void GameScene::update(float delat){
	checkOutCollision();
}

//判断碰撞
void GameScene::checkOutCollision()
{
	Weapon* weapon = _cannonLayer->getWeapon();
	if (weapon->weaponStatus() == k_Weapon_Status_Bullet){
		bool flag = this->checkOutCollisionBetweenFishesAndBullet();
		if (flag){
			this->checkOutCollisionBetweenFishesAndFishingNet();
		}
	}
}

//判断鱼和子弹的碰撞
bool GameScene::checkOutCollisionBetweenFishesAndBullet()
{
	Weapon* weapon = _cannonLayer->getWeapon();
	CCPoint bulletCollision = weapon->getCollisionPoint();
	CCArray* fishes = _fishLayer->getFishes();
	CCObject* iterator;
	CCARRAY_FOREACH(fishes, iterator){
		Fish* fish = (Fish*)iterator;
		//isRunnning判断fish是否已经在屏幕上显示
		if (fish->isRunning()){
			CCRect fishCollisionArea = fish->getCollisionArea();
			//判断鱼的碰撞区域是否包含子弹的坐标
			bool isCollision = fishCollisionArea.containsPoint(bulletCollision);
			if (isCollision){
				//如果碰撞，结束子弹的飞行
				weapon->end();
				return true;
			}
		}
	}
	return false;
}

//判断捕获的鱼
void GameScene::checkOutCollisionBetweenFishesAndFishingNet()
{
	Weapon* weapon = _cannonLayer->getWeapon();
	CCRect bulletCollision = weapon->getCollisionArea();
	CCArray* fishes = _fishLayer->getFishes();
	CCObject* iterator;
	CCARRAY_FOREACH(fishes, iterator){
		Fish* fish = (Fish*)iterator;
		//isRunnning判断fish是否已经在屏幕上显示
		if (fish->isRunning()){
			CCRect fishCollisionArea = fish->getCollisionArea();
			bool isCollision = fishCollisionArea.intersectsRect(bulletCollision);
			if (isCollision){
				this->fishWillBeCaught(fish);
			}
		}
	}
}

void GameScene::fishWillBeCaught(Fish* fish)
{
	int weaponType = _cannonLayer->getWeapon()->getCannonType();
	int fishType = fish->getType();
	float fish_percentage = STATIC_DATA_FLOAT(CCString::createWithFormat(STATIC_DATA_STRING("fish_percentage_format"), fishType)->getCString());
	float weapon_percentage = STATIC_DATA_FLOAT(CCString::createWithFormat(STATIC_DATA_STRING("weapon_percentage_format"), weaponType)->getCString());
	float percentage = weapon_percentage * fish_percentage;
	if (CCRANDOM_0_1() < percentage){
		fish->beCaught();
		//增加金币
		int reward = STATIC_DATA_INT(CCString::createWithFormat(STATIC_DATA_STRING("reward_format"), fishType)->getCString());
		this->alterGold(reward);
	}
}

//操作所有节点
void GameScene::operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag)
{
	if (node->isRunning()){
		switch (flag) {
		case k_Operate_Pause:
			node->pauseSchedulerAndActions();
			break;
		case k_Operate_Resume:
			node->resumeSchedulerAndActions();
			break;
		default:
			break;
		}
		CCArray* array = node->getChildren();
		if (array != NULL && array->count() > 0){
			CCObject* iterator;
			CCARRAY_FOREACH(array, iterator){
				CCNode* child = (CCNode*)iterator;
				this->operateAllSchedulerAndActions(child, flag);
			}
		}
	}
}

//金币改变
void GameScene::alterGold(int delta)
{
	FishingJoyData::sharedFishingJoyData()->alterGold(delta);
	_panelLayer->getGoldCounterLayer()->setNumber(FishingJoyData::sharedFishingJoyData()->getGold());
}

//金币随时间增加
void GameScene::scheduleTimeUp()
{
	this->alterGold(STATIC_DATA_INT("recovery_gold"));
}