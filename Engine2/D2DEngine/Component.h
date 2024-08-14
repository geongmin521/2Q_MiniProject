#pragma once


class GameObject;
class Component
{
private:
	bool isActive = true;

public:
	GameObject* owner;
public:
	Component();
	virtual ~Component();
	void setActive(bool active);
	bool getActive() { return isActive; }
	void SetOwner(GameObject* pOwner) { owner = pOwner; }

	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* pRenderTarget,float Alpha = 1);

	virtual void Enable();
	virtual void Disable();
};
