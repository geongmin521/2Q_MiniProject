#include "pch.h"
#include "ProductionCamera.h"
#include "InputSystem.h"
#include "Transform.h"
#include "CameraScene.h"
#include "Dotween.h"

ProductionCamera::ProductionCamera()
{
	AddComponent(new CameraScene());
}

void ProductionCamera::Update(float deltaTime)
{
	__super::Update(deltaTime);

	if (inputSystem->GetInstance()->isKeyDown(VK_F1))
	{
		BossAwake();
	}

	if (inputSystem->GetInstance()->isKeyDown(VK_F2))
	{
		ResetPos();
	}
}

void ProductionCamera::BossAwake()
{
	auto& scale = transform->relativeScale;
	auto& loca = transform->relativeLocation;

	new DOTween(loca.x, EasingEffect::InSine, StepAnimation::StepOnceForward, 3.0f, loca.x, loca.x + 700);
	new DOTween(loca.y, EasingEffect::InSine, StepAnimation::StepOnceForward, 3.0f, loca.y, loca.y + 200);
	
	new DOTween(scale.x, EasingEffect::InSine, StepAnimation::StepOnceForward, 3.0f, 1, 0.6f);
	new DOTween(scale.y, EasingEffect::InSine, StepAnimation::StepOnceForward, 3.0f, 1, 0.6f);
}

void ProductionCamera::ResetPos()
{
	auto& scale = transform->relativeScale;
	auto& loca = transform->relativeLocation;

	new DOTween(loca.x, EasingEffect::InSine, StepAnimation::StepOnceForward, 3.0f, loca.x, loca.x - 700);
	new DOTween(loca.y, EasingEffect::InSine, StepAnimation::StepOnceForward, 3.0f, loca.y, loca.y - 200);

	new DOTween(scale.x, EasingEffect::InSine, StepAnimation::StepOnceForward, 3.0f, 0.6f, 1.0f);
	new DOTween(scale.y, EasingEffect::InSine, StepAnimation::StepOnceForward, 3.0f, 0.6f, 1.0f);
}

