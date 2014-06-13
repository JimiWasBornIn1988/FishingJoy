#ifndef __FishingJoy__Counter__
#define __FishingJoy__Counter__
#include "cocos2d.h"
class Counter : public cocos2d::CCNode	
{
public:
	Counter();
	/**
	*	@brief
	*
	*	@param 	presenters 	0-9��10�����ֶ�Ӧ�Ľڵ������
	*	@param 	digit 	Ĭ�ϵ���ֵ
	*
	*	@return
	*/
	static Counter* create(cocos2d::CCArray* presenters, int digit = 0);
	bool init(cocos2d::CCArray* presenters, int digit = 0);
	CC_PROPERTY(int, _digit, Digit);
protected:
	void visit();
	//���0-9���ֶ�Ӧ�Ľڵ�
	cocos2d::CCNode* _presenters;
	//�ı�����ʱ���Ź�������
	void animation(int digit);
};

#endif /* defined(__FishingJoy__Counter__) */

