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
        var->Update(deltaTime); //������Ʈ �������� �����     //�ð��� ������ �ڵ� �Ҹ����������ڴµ�..   
}
