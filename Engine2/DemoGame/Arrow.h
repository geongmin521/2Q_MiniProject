#pragma once
#include "GameObject.h"


class Arrow : public GameObject , IColliderNotify
{
private:
    float speed = 0.3f;
public:
    Arrow(std::string type, float damage, float attackArea, float knockBack);
    virtual ~Arrow();
    GameObject* target;
    MathHelper::Vector2F preDir;
    MathHelper::Vector2F curDir;
    std::string type;
    float knockBack;
    float duration = 2.0f;
    float elapsedTime;
    float attackTime = 0.1f;
    float elapsedTime2;

    std::function<void()> AttackFunc;
    void Init(MathHelper::Vector2F location, GameObject* target = nullptr);

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1);

    virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent)        override;
    virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)  override;
    virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)   override;
};

