#pragma once
#include "World.h"

class Shop;
class D2DFont; 
class ShowWave;
class GameObject;
class BattleWorld : public World
{
private:
	Shop* shop;					//���� UI
	D2DFont* WaveCount;			//���̺�ī��Ʈ
	D2DFont* goldText;				//��ȭ�ؽ�Ʈ
	ShowWave* showWave;			//�� ���̺� UI
	std::map<std::string, GameObject*> Objs;//���ΰ����ϴ� ������Ʈ
public:

	BattleWorld(); 
	virtual ~BattleWorld();
	void MakeObject() override;
	void MakeUI();
	void RegisterEvent();
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha = 1);
};

