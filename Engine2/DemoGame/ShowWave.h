#pragma once
#include "UI.h"

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

};
