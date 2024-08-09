#pragma once
#include "SingletonBase.h"
class DOTween;
class DOTweenManager:public SingletonBase<DOTweenManager>
{
private:
    std::vector<DOTween*> tweens;
public:
    DOTweenManager(); //둘다 알필요없이 하나만 알면 만들수있을려면.. 
    ~DOTweenManager();
    void PushTween(DOTween* tween) { tweens.push_back(tween); }
    void EraseTween(DOTween* tween) {
        tweens.erase(std::remove(tweens.begin(), tweens.end(), tween), tweens.end());
    }
    void Update(float deltaTime);

};

