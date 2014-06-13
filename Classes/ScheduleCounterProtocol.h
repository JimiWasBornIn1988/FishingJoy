#ifndef __FishingJoy__ScheduleCounterProtocol__
#define __FishingJoy__ScheduleCounterProtocol__
class ScheduleCounterDelegate
{
public:
	/**
	*	@brief	    Required
	*/
	virtual void scheduleTimeUp() = 0;
	/**
	*	@brief	    Optional
	*
	*	@param 	number 	��Ҫ���õ�����
	*/
	virtual void setScheduleNumber(int number){ return; };
};

#endif /* defined(__FishingJoy__ScheduleCounterProtocol__) */
