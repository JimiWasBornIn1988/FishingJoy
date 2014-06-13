#ifndef __FishingJoy__Weapon__
#define __FishingJoy__Weapon__
#include "cocos2d.h"
#include "Cannon.h"
#include "Bullet.h"
#include "FishingNet.h"
enum {
	k_Weapon_Status_None = 0,
	k_Weapon_Status_Bullet,
	k_Weapon_Status_FishingNet
};
class Weapon:public  cocos2d::CCNode
{
public:
	static Weapon* create(CannonType type = k_Cannon_Type_1);
	bool init(CannonType type = k_Cannon_Type_1);

	//控制函数
	bool shootTo(cocos2d::CCPoint touchLocation);
	void aimAt(cocos2d::CCPoint target);
	//碰撞点
	cocos2d::CCPoint getCollisionPoint();
	//碰撞区域
	cocos2d::CCRect getCollisionArea();
	void end();

	CC_SYNTHESIZE_READONLY(Cannon*,_cannon,Cannon);
	CC_SYNTHESIZE_READONLY(Bullet*, _bullet, Bullet);
	CC_SYNTHESIZE_READONLY(FishingNet*, _fishingNet, FishingNet);
	int getCannonType();
	//武器状态
	int weaponStatus();
protected:
	//通过ParticleDesigner加载的粒子效果
	cocos2d::CCParticleSystemQuad* _particle;
};

#endif /* defined(__FishingJoy__Weapon__) */
