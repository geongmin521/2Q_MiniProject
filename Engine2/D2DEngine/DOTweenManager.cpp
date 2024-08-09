#include "pch.h"
#include "DOTweenManager.h"
#include "Dotween.h"

DOTweenManager::DOTweenManager()
{
}

DOTweenManager::~DOTweenManager()
{
}

void DOTweenManager::Update(float deltaTime)
{
    for (auto var : tweens)
        var->Update(deltaTime); //업데이트 돌리도록 만들고     //시간이 지나면 자동 소멸했으면좋겠는데..   
}
