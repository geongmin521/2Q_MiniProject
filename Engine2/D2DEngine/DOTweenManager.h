#pragma once
#include "SingletonBase.h"
class DOTween;
class DOTweenManager:public SingletonBase<DOTweenManager>
{
private:
    std::list<DOTween*> tweens;
    std::list<DOTween*> removetweens;
public:
    DOTweenManager();
    ~DOTweenManager();
    void PushTween(DOTween* tween) { tweens.push_back(tween); }
    void EraseTween(DOTween* tween) { removetweens.push_back(tween); }
    void Update(float deltaTime);

};

