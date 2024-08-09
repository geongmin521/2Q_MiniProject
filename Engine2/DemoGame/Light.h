#pragma once
#include "../D2DEngine/GameObject.h"

class D2DFont;
class Light : public GameObject , IColliderNotify
{
public:
	Light();
	~Light();

	bool test = false;

	void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

	virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent);
	virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent);
	virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent);
	virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent);
};

