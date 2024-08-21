#pragma once
#include "SingletonBase.h"

#define dotweenManager DOTweenManager::GetInstance().get()

class DOTween;
class DOTweenManager:public SingletonBase<DOTweenManager>
{
private:
    std::list<DOTween*> tweens;
    std::list<DOTween*> removetweens;
public:
    DOTweenManager();
    ~DOTweenManager();
    virtual void reset() override;
    void PushTween(DOTween* tween) { 
        tweens.push_back(tween); 
    }
    void EraseTween(DOTween* tween) {
        removetweens.push_back(tween);
    }
    void Update(float deltaTime);

};

