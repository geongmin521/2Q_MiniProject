#pragma once
#include "SingletonBase.h"
class DOTween;
class DOTweenManager:public SingletonBase<DOTweenManager>
{
private:
    std::vector<DOTween*> tweens;
public:
    DOTweenManager(); //�Ѵ� ���ʿ���� �ϳ��� �˸� �������������.. 
    ~DOTweenManager();
    void PushTween(DOTween* tween) { tweens.push_back(tween); }
    void EraseTween(DOTween* tween) {
        tweens.erase(std::remove(tweens.begin(), tweens.end(), tween), tweens.end());
    }
    void Update(float deltaTime);

};

