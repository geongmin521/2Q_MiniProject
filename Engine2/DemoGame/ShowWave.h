#pragma once
#include "UI.h"

class WaveData;
class Image;
class ShowWave :public UI
{
private:
	Image* images[4];
public:
	ShowWave();
	~ShowWave();

	bool isMid = false;
	bool isExit = false;
	float elapsedTime;
	float middleTime = 1.5f; //중앙에 있을시간
	void Update(float deltatime);
	void Show();

};
