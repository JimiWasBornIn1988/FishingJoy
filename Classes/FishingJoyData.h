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
	 *@brief �ڴ治��ʱ����
	 */
	void purge();
	/**
	 *@brief �����ݱ��浽�ⲿ�ļ�
	 */
	void flush();
	/**
	 *@brief ��gold�Ĳ���
	 *@param delta ��������
	 */
	void alterGold(int delta);
    /**
	 *@brief ������Ϸ����
	 */
	void reset();
protected:
	FishingJoyData();
	~FishingJoyData();
	bool init();
};

#endif // !__FishingJoy__FishingJoyData__