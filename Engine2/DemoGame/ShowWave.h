#pragma once
#include "UI.h"

class WaveData;
class Image;
class D2DFont;
class ShowWave :public UI
{
private:
	Image* images[4];
	D2DFont* text;
public:
	ShowWave();
	~ShowWave();

	bool isMid = false;
	bool isExit = false;
	float elapsedTime;
	float middleTime = 4.5f; //중앙에 있을시간
	void Update(float deltatime);
	void Show();

};
