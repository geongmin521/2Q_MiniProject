#pragma once
#include "../D2DEngine/UI.h"

class WaveData;
class ShowWave :public UI
{
private:
	std::vector<GameObject*> sprites; //������ �����̹���.. //��� �� �ΰ��γ�����? 
	//�� �κк��� ���� �����������ϱ�.. ����ɼ��ִ� �ֵ鸸 ���� �������ſ���? 
	std::vector<GameObject*> exitButton; //������ �����Լ�
	WaveData* wave;
	//Ȥ�ø𸣴� �׳� ������ ��ü�� �����صѱ�?
public:
	ShowWave();
	~ShowWave();
	void Show();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};
