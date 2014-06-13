#ifndef __FishingJoy__Fish__
#define __FishingJoy__Fish__
#include "cocos2d.h"
typedef enum{
	k_Fish_Type_Red = 0,
	k_Fish_Type_Yellow,
	k_Fish_Type_Count
}FishType;
//�̳��Խڵ� CCNode
class Fish : public cocos2d::CCNode
{
public:
	static Fish* create(FishType type = k_Fish_Type_Red);
	bool init(FishType type = k_Fish_Type_Red);

	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, _fishSprite, FishSprite);
	CC_SYNTHESIZE_READONLY(int, _type, Type);
	cocos2d::CCRect getCollisionArea();
	//���ű���׽�Ķ���
	void beCaught();

	//�ƶ��㵽destination
	void moveTo(cocos2d::CCPoint destination);
	//�������״̬
	void reset();
protected:
	void moveEnd();
	void beCaught_CallFunc();
};

#endif /* defined(__FishingJoy__Fish__) */
