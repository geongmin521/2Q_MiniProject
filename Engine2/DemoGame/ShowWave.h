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
	float middleTime = 3.0f; //�߾ӿ� �����ð�
	void Update(float deltatime);
	void Show();

};
