#pragma once
#include "GameObject.h"
class Effect : public GameObject
{

	float duration = 0; //����Ʈ �����ð�
	float elapsedTime = 0;
public:
	Effect();
	Effect(MathHelper::Vector2F location,float _duration);
	virtual ~Effect();
	
	void Init(std::wstring imagePath, MathHelper::Vector2F location, float _duration); //init���� �� ��Ʈ�� �ִϸ��̼� �����ߴٰ� �������ϳ�?
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha = 1);
};

