#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/IColliderNotify.h" 

class SpiderWeb;
class Character :
    public GameObject, public IColliderNotify
{
private:
	float speed;
	float Jumpspeed; 


public:
	Character();
	void Jump();
	virtual ~Character();	
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

	virtual void OnBlock		(Collider* pOtherComponent) override;
	virtual void OnBeginOverlap (Collider* pOtherComponent) override;
	virtual void OnEndOverlap	(Collider* pOtherComponent) override;
	bool alive = true;
	bool isground = false;
	bool ishanging = false;
	float MoveY = 0;

	SpiderWeb* web;
};

