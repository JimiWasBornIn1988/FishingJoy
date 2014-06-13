#ifndef FishingJoy_ProgressProtocol_h
#define FishingJoy_ProgressProtocol_h
class ProgressDelegate
{
public:
	virtual void loadingFinished() = 0;
	virtual void progressPercentageSetter(float percentage){ return; };
};
#endif
