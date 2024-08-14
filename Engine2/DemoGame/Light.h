#pragma once
#include "GameObject.h"
#include "IColliderNotify.h"
#include "IEffect.h"

class Bitmap;
class Light : public GameObject , IColliderNotify, IEffect
{
public:
	Light();
	~Light();

	void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

	virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent);
	virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent);
	virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent);
	virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent);

	Transform* LightTransform;

	Bitmap* firstBitmap = nullptr;
	Bitmap* secondBitmap = nullptr;

	bool test = true;

	virtual void EffectUpdate(float deltaTime);
	virtual void EffectRender();
};

