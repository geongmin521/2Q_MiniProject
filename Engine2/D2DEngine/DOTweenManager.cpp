#include "pch.h"
#include "DOTweenManager.h"
#include "Dotween.h"
#include "GameManager.h"
#include "Utility.h"

DOTweenManager::DOTweenManager()
{
    gameManager->Reset.push_back([this]() { reset(); });
}

DOTweenManager::~DOTweenManager()
{
}

void DOTweenManager::reset()
{
    tweens.clear();
    removetweens.clear();
}

void DOTweenManager::Update(float deltaTime)
{
    if (removetweens.size() != 0)
        Utility::removeElements(tweens, removetweens);
    removetweens.clear();
    for (auto var : tweens)    
        var->Update(deltaTime);  
}
