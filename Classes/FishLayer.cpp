#include "FishLayer.h"
USING_NS_CC;

bool FishLayer::init(){
	if (CCLayer::init()){
		int capacity = 50;
		_fishes = CCArray::createWithCapacity(capacity);
		CC_SAFE_RETAIN(_fishes);
		for (int i = 0; i < capacity;++i){
			//0-2 枚举的值
			int type = CCRANDOM_0_1() * 2;
			Fish* fish = Fish::create((FishType)type);
			_fishes->addObject(fish);
			this->schedule(schedule_selector(FishLayer::addFish), 3.0);
		}
		return true;
	}
	return false;
}

void FishLayer::addFish(float dt){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//随机增加Fish
	int countToAdd = CCRANDOM_0_1() * 20 + 1;
	int countHasAdded = 0;
	CCObject* iterator;
	CCARRAY_FOREACH(_fishes, iterator){
		Fish* fish = (Fish*)iterator;
		if (fish->getParent() == NULL){
			this->addChild(fish);
			this->resetFish(fish);
			countHasAdded++;
			if (countHasAdded == countToAdd){
				break;
			}
		}
	}
}

void FishLayer::resetFish(Fish* fish)
{
	fish->reset();
	CCPoint start, destination;
	float startX, startY, endX, endY;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize fishSize = fish->getFishSprite()->getContentSize();
	int direction = CCRANDOM_0_1() * 2;
	if (direction){
		fish->setRotation(180);
		startX = winSize.width + fishSize.width*0.5;
		endX = -fishSize.width*0.5;
	}
	else{
		fish->setRotation(0);
		startX = -fishSize.width*0.5;
		endX = winSize.width + fishSize.width*0.5;
	}
	startY = CCRANDOM_0_1()*(winSize.height - 2 * fishSize.height) + fishSize.height;
	endY = CCRANDOM_0_1()*(winSize.height - 2 * fishSize.height) + fishSize.height;

	start = CCPointMake(startX, startY);
	destination = CCPointMake(endX, endY);
	fish->setPosition(start);
	fish->moveTo(destination);
}

FishLayer::~FishLayer()
{
	CC_SAFE_RELEASE(_fishes);
}
