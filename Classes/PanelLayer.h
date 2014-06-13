#ifndef __FishingJoy__PanelLayer__
#define __FishingJoy__PanelLayer__
#include "cocos2d.h"
#include "GoldCounterLayer.h"
#include "ScheduleCounterProtocol.h"
class PanelLayer :public cocos2d::CCLayer, public ScheduleCounterDelegate
{
public:
	CREATE_FUNC(PanelLayer);
	bool init();
	CC_SYNTHESIZE_READONLY(GoldCounterLayer*, _goldCounterLayer, GoldCounterLayer);
	CC_SYNTHESIZE_READONLY(cocos2d::CCMenu*, _menu, Menu);
	//ScheduleCounterDelegate
	void scheduleTimeUp();
	void setScheduleNumber(int number);
	void setMenuTouchEnabled(bool flag);

protected:
	void pause(cocos2d::CCObject* pSender);
	cocos2d::CCLabelTTF* _scheduleLabel;
};
#endif /* defined(__FishingJoy__PanelLayer__) */
