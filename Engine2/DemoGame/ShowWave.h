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
	void Show();

};
