#pragma once
#include "World.h"

class Shop;
class D2DFont; 
class ShowWave;
class GameObject;
class Button;
class BattleWorld : public World
{
private:
	Shop* shop;					//���� UI
	D2DFont* goldText;			//��ȭ�ؽ�Ʈ
	ShowWave* showWave;			//�� ���̺� UI
	Button* TimeScaleButton[3];
	std::map<std::string, GameObject*> Objs; //���ΰ����ϴ� ������Ʈ

	D2DFont* BossDialogue;			// ���� ���
public:

	BattleWorld(); 
	virtual ~BattleWorld();
	void MakeObject() override;
	void MakeUI();
	void RegisterEvent();
	void TimeScaleIsClick(int num);
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha = 1);
};

