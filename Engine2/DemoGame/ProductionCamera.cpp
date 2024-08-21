#include "pch.h"
#include "ProductionCamera.h"
#include "InputSystem.h"
#include "Transform.h"
#include "CameraScene.h"
#include "Dotween.h"
#include "World.h"
#include "EnemyBase.h"
ProductionCamera::ProductionCamera()
{
	AddComponent(new CameraScene());
}

void ProductionCamera::Update(float deltaTime)
{
	__super::Update(deltaTime);


#if(_DEBUG)
	if (inputSystem->GetInstance()->isKeyDown(VK_F1))
	{
		BossAwake();
	}

	if (inputSystem->GetInstance()->isKeyDown(VK_F2))
	{
		ResetPos();
	}

	if (inputSystem->GetInstance()->isKeyDown(VK_F3))
	{
		Earthquake();
	}
#endif


	if (isEarthquake == true)
	{
		EarthquakeTime += deltaTime;
		if (EarthquakeTime > 3.f)
		{
			EarthquakeTime = 0;
			ReseEarthquake();
			isEarthquake = false;
		}
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

	EnemyBase* FindEnemy;
	
	for (auto& GameObject : owner->m_GameObjects)
	{
		if (GameObject->name.empty()) { continue; }
		if (GameObject->name == "Enemy")
		{
			FindEnemy = dynamic_cast<EnemyBase*>(GameObject);
			if (FindEnemy->enemyData.name != "Boss") { continue; }
			else
			{
				FindEnemy->isProduction = false;
				FindEnemy->isStoppage = true;
			}
		}
	}

}

void ProductionCamera::Earthquake()
{
	auto& loca = transform->relativeLocation;
	auto& scale = transform->relativeScale;

	new DOTween(scale.x, EasingEffect::InSine, StepAnimation::StepOnceForward, 3.0f, 0.95f, 0.8f);
	new DOTween(scale.y, EasingEffect::InSine, StepAnimation::StepOnceForward, 3.0f, 0.95f, 0.8f);

	new DOTween(loca.x, EasingEffect::InOutBounce, StepAnimation::StepOnceForward, 3.0f, loca.x, loca.x + 100);
	new DOTween(loca.y, EasingEffect::InOutBounce, StepAnimation::StepOnceForward, 3.0f, loca.y, loca.y + 100);

	isEarthquake = true;
}

void ProductionCamera::ReseEarthquake()
{
	auto& loca = transform->relativeLocation;
	auto& scale = transform->relativeScale;

	new DOTween(loca.x, EasingEffect::InOutBounce, StepAnimation::StepOnceForward, 3.0f, loca.x, loca.x - 100);
	new DOTween(loca.y, EasingEffect::InOutBounce, StepAnimation::StepOnceForward, 3.0f, loca.y, loca.y - 100);

	new DOTween(scale.x, EasingEffect::InSine, StepAnimation::StepOnceForward, 3.0f, 0.8f, 1.0f);
	new DOTween(scale.y, EasingEffect::InSine, StepAnimation::StepOnceForward, 3.0f, 0.8f, 1.0f);
}

