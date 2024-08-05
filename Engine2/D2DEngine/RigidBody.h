#pragma once
#include "Component.h"
//#include "AABB.h"

class Transform;
class AABB;
class RigidBody :
    public Component
{
private:
	bool isGravity;
	float gravityScale;// 중력은 바꾸고 싶을수도 있는데..
public:

	RigidBody();
	virtual ~RigidBody();
	virtual void Update(float deltaTime);
	//virtual void Render(ID2D1RenderTarget* pRenderTarget); //그릴거는 딱히 없는듯.. 
	virtual void Enable() override;
	virtual void Disable() override;

	float getGravity() { return gravityScale; }
	void resetGravity() {  gravityScale = 0; }

};

