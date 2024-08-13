#pragma once
#include "GameObject.h"


class Arrow : public GameObject , IColliderNotify
{
private:
    float speed = 0.3f;
public:
    Arrow(float speed, std::string type, float damage, float attackArea);
    virtual ~Arrow();
    GameObject* target;
    MathHelper::Vector2F preDir;
    MathHelper::Vector2F curDir;
    std::function<void(void)> AttackFunc;
    void Init(GameObject* target, MathHelper::Vector2F location); 
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1);

    virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent)        override;
    virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)  override;
    virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)   override;
};

