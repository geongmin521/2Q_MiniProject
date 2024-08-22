#pragma once
#include "SingletonBase.h"

#define timeManager TimeManager::GetInstance().get()

class TimeManager: public SingletonBase<TimeManager>
{
public:
	TimeManager();
	~TimeManager();
	virtual void reset() override;
	void InitTime();
	void UpdateTime();
	const float GetFrameRate();
	const float GetDeltaTime();

	void SetTimeScale(float scale);
	float GetTimeScale() { return _TimeScale; }

	void SetBeforeTimeScale(float _scale) { _BeforeTimeScale = _scale; }
	float GetBeforeTimeScale() { return _BeforeTimeScale; }
private:
	LARGE_INTEGER _CurTime;
	LARGE_INTEGER _PrevTime;
	LARGE_INTEGER _Frequency;

	float _DeltaTime;
	float _TimeScale;
	float _BeforeTimeScale = 2.f;
};