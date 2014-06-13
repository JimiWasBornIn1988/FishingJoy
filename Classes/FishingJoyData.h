#ifndef __FishingJoy__FishingJoyData__
#define __FishingJoy__FishingJoyData__
#include "cocos2d.h"
class FishingJoyData:public cocos2d::CCObject
{
public:
	static FishingJoyData* sharedFishingJoyData();
	CC_SYNTHESIZE(int, _gold, Gold);
	CC_SYNTHESIZE(bool, _isBeginner, IsBeginner);
	CC_SYNTHESIZE(float, _soundVolume, SoundVolume);
	CC_SYNTHESIZE(float, _musicVolume, MusicVolume);

	/**
	 *@brief 内存不足时调用
	 */
	void purge();
	/**
	 *@brief 将数据保存到外部文件
	 */
	void flush();
	/**
	 *@brief 对gold的操作
	 *@param delta 正负均可
	 */
	void alterGold(int delta);
    /**
	 *@brief 重置游戏数据
	 */
	void reset();
protected:
	FishingJoyData();
	~FishingJoyData();
	bool init();
};

#endif // !__FishingJoy__FishingJoyData__
