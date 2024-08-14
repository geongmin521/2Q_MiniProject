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
    for (auto var : tweens)    
        var->Update(deltaTime);  
}
