#pragma once


class GameObject;
class Component
{

private:
	bool isActive = true;
	virtual void Enable();	//isActive 가 true가 될때 호출
	virtual void Disable();	//isActive 가 false가 될때 호출
public:
	Component();
	virtual ~Component();

	GameObject* owner;

public:
	void setActive(bool active);
	bool getActive() { return isActive; }
	void SetOwner(GameObject* pOwner) { owner = pOwner; }

	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);


};

//pch가 항상위면 생기지않지않나?
//트랜스폼 aabb 게임오브젝트 헤더가 꼬인거같은데.. 이들의 순서관계는 상관없겠지?