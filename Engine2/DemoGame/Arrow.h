#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/IColliderNotify.h"

class Arrow : public GameObject, IColliderNotify
{
private:
    float speed = 1000.0f;
public:
    Arrow();
    virtual ~Arrow();
    
    void Init(MathHelper::Vector2F velocity, MathHelper::Vector2F location); //방향, 위치?
    void Init(GameObject* target); //방향, 위치?
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);


    virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent) override;
};