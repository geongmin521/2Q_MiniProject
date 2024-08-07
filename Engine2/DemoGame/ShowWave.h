#pragma once
#include "../D2DEngine/UI.h"

class WaveData;
class ShowWave :public UI
{
private:
	std::vector<GameObject*> sprites; //적들이 나올이미지.. //얘는 왜 두개로나눴지? 
	//아 부분별로 끄고 켜질수있으니까.. 변경될수있는 애들만 따로 빼놓은거였지? 
	std::vector<GameObject*> exitButton; //적들이 종료함수
	WaveData* wave;
	//혹시모르니 그냥 데이터 자체를 저장해둘까?
public:
	ShowWave();
	~ShowWave();
	void Show();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};
