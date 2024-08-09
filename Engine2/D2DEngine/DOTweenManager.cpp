#include "pch.h"
#include "DOTweenManager.h"
#include "Dotween.h"
#include "Utility.h"

DOTweenManager::DOTweenManager()
{
}

DOTweenManager::~DOTweenManager()
{
}

void DOTweenManager::Update(float deltaTime)
{
    if (removetweens.size() != 0)
        Utility::removeElements(tweens, removetweens);
    for (auto var : tweens) //아 중간에 돌다가 지워서 그렇구나.. 
        var->Update(deltaTime); //업데이트 돌리도록 만들고     //시간이 지나면 자동 소멸했으면좋겠는데..   
}
