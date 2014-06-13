
#ifndef __FishingJoy__StartScene__
#define __FishingJoy__StartScene__
#include "cocos2d.h"
#include "ProgressProtocol.h"
#include "ProgressBar.h"

USING_NS_CC;

class StartLayer : public cocos2d::CCLayer, public ProgressDelegate
{
public:
	static cocos2d::CCScene* scene();
	bool init();
	CREATE_FUNC(StartLayer);
	void loadingFinished();
	void progressPercentageSetter(float percentage);

protected:
	ProgressBar* _progressBar;
	cocos2d::CCLabelTTF* _progressFg;
	void transition(CCObject* pSender);
	void loading(CCObject* pObj);
	//加载缓存
	void cacheInit();
	//音频加载
	void audioAndUserDataInit();
	//加载完成后
	void initializationCompleted();
};
#endif /* defined(__FishingJoy__StartScene__) */
