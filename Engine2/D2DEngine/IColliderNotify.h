#pragma once

class Collider;
class IColliderNotify 
{
public:
	virtual void OnBlock		(Collider* ownedComponent, Collider* otherComponent) = 0;
	virtual void OnBeginOverlap (Collider* ownedComponent, Collider* otherComponent) = 0;
	virtual void OnStayOverlap (Collider* ownedComponent, Collider* otherComponent) = 0; 
	virtual void OnEndOverlap	(Collider* ownedComponent, Collider* otherComponent) = 0; 
};
