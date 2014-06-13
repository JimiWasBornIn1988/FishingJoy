#ifndef __FishingJoy__GameScene__
#define __FishingJoy__GameScene__
#include "cocos2d.h"
#include "FishLayer.h"
#include "PanelLayer.h"
#include "MenuLayer.h"
#include "BackgroundLayer.h"
#include "CannonLayer.h"
#include "TouchLayer.h"

typedef enum{
	k_Operate_Pause = 0,
    k_Operate_Resume
}OperateFlag;

class GameScene:public cocos2d::CCScene
{
public:
	CREATE_FUNC(GameScene);
	bool init();
	~GameScene();

	//菜单页面相关函数
	void pause();
	void resume();
	void sound();
	void music();
	void reset();
	void transToMainMenu();
	//触摸页面相关的函数
	void cannonAimAt(cocos2d::CCPoint target);//炮台瞄准
	void cannonShootTo(cocos2d::CCPoint target);//开炮
	//处理计时
	void scheduleTimeUp();

protected:
	BackgroundLayer* _backgroundLayer;
	CannonLayer* _cannonLayer;
	FishLayer* _fishLayer;
	PanelLayer* _panelLayer;
	MenuLayer* _menuLayer;
	TouchLayer* _touchLayer;
	void update(float delat);

	//碰撞检测相关
	void checkOutCollision();
	bool checkOutCollisionBetweenFishesAndBullet();
	void checkOutCollisionBetweenFishesAndFishingNet();

	void fishWillBeCaught(Fish* fish);

	//暂停或恢复所有节点
	void operateAllSchedulerAndActions(cocos2d::CCNode* node,OperateFlag flag);
	//数据相关
	void alterGold(int delta);
	void onEnterTransitionDidFinish();

};

#endif /* defined(__FishingJoy__GameScene__) */
