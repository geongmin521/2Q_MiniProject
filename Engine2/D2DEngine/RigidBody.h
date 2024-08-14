#pragma once
#include "Component.h"

class Transform;
class AABB;
class RigidBody :
    public Component
{
private:
	bool isGravity;
	float gravityScale;
public:

	RigidBody();
	virtual ~RigidBody();
	virtual void Update(float deltaTime);
	virtual void Enable() override;
	virtual void Disable() override;

	float getGravity() { return gravityScale; }
	void resetGravity() {  gravityScale = 0; }

};

