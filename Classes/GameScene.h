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

	//�˵�ҳ����غ���
	void pause();
	void resume();
	void sound();
	void music();
	void reset();
	void transToMainMenu();
	//����ҳ����صĺ���
	void cannonAimAt(cocos2d::CCPoint target);//��̨��׼
	void cannonShootTo(cocos2d::CCPoint target);//����
	//�����ʱ
	void scheduleTimeUp();

protected:
	BackgroundLayer* _backgroundLayer;
	CannonLayer* _cannonLayer;
	FishLayer* _fishLayer;
	PanelLayer* _panelLayer;
	MenuLayer* _menuLayer;
	TouchLayer* _touchLayer;
	void update(float delat);

	//��ײ������
	void checkOutCollision();
	bool checkOutCollisionBetweenFishesAndBullet();
	void checkOutCollisionBetweenFishesAndFishingNet();

	void fishWillBeCaught(Fish* fish);

	//��ͣ��ָ����нڵ�
	void operateAllSchedulerAndActions(cocos2d::CCNode* node,OperateFlag flag);
	//�������
	void alterGold(int delta);
	void onEnterTransitionDidFinish();

};

#endif /* defined(__FishingJoy__GameScene__) */
