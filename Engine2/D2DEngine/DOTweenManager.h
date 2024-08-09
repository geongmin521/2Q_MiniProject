#pragma once
#include "SingletonBase.h"
class DOTween;
class DOTweenManager:public SingletonBase<DOTweenManager>
{
private:
    std::list<DOTween*> tweens;
    std::list<DOTween*> removetweens;
public:
    DOTweenManager(); //둘다 알필요없이 하나만 알면 만들수있을려면.. 
    ~DOTweenManager();
    void PushTween(DOTween* tween) { tweens.push_back(tween); }
    void EraseTween(DOTween* tween) { removetweens.push_back(tween); }
    void Update(float deltaTime);

};

