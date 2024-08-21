#include "pch.h"
#include "TimeSystem.h"
#include "GameManager.h"

TimeManager::TimeManager() : _CurTime{ 0 }, _PrevTime{ 0 }, _Frequency{ 0 } , _DeltaTime(0), _TimeScale(1.0f)
{
	gameManager->Reset.push_back([this]() { reset(); });
}

TimeManager::~TimeManager()
{
}

void TimeManager::reset()
{
}

void TimeManager::InitTime()
{
	QueryPerformanceFrequency(&_Frequency);
	QueryPerformanceCounter(&_CurTime);
}

void TimeManager::UpdateTime()
{
	_PrevTime = _CurTime;
	QueryPerformanceCounter(&_CurTime);

	_DeltaTime = (float)(_CurTime.QuadPart - _PrevTime.QuadPart) / ((float)(_Frequency.QuadPart));
	_DeltaTime *= _TimeScale;

//#ifdef _DEBUG
//	if (_DeltaTime > (1.f / 60.f)) {
//		_DeltaTime = (1.f / 60.f);
//	}
//#endif
}

const float TimeManager::GetFrameRate()
{
	if (_DeltaTime == 0) return 0;

	return ceil(((1.0f / _DeltaTime)));
}

const float TimeManager::GetDeltaTime()
{
	return _DeltaTime;
}

void TimeManager::SetTimeScale(float scale)
{
	_DeltaTime = 0;
	_TimeScale = scale;
}
