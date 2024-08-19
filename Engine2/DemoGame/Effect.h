#pragma once
#include "GameObject.h"
class Effect : public GameObject
{

	float duration = 0; //����Ʈ �����ð�
	float elapsedTime = 0;
public:
	Effect(int id, std::string imagepath, std::string csvpath,bool isAni =true);
	virtual ~Effect();
	
	void Init(std::wstring imagePath, MathHelper::Vector2F location, float _duration = 0); 
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha = 1);
};

