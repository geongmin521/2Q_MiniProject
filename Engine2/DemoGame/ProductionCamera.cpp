#include "pch.h"
#include "ProductionCamera.h"
#include "InputSystem.h"
#include "Transform.h"
#include "CameraScene.h"
#include "Dotween.h"
#include "World.h"
#include "EnemyBase.h"

#include "Image.h"
#include "TimeSystem.h"
#include "Music.h"

ProductionCamera::ProductionCamera()
{
	AddComponent(new CameraScene());
}

void ProductionCamera::Update(float deltaTime)
{
	__super::Update(deltaTime);

	if (isEarthquake == true) // ������ ���ư���
	{
		EarthquakeTime += deltaTime;
		if (EarthquakeTime > 3.0f)
		{
			EarthquakeTime = 0;
			ReseEarthquake();
			isEarthquake = false;
		}
	}

	if (istest == true) // ���� Ȯ��
	{
		EarthquakeTime += deltaTime;
		if (EarthquakeTime > 3.0f)
		{
			EarthquakeTime = 0;
			BossAwake(deltaTime);
			istest = false;
		}
	}

	if (isDialogueDelay == true) // ���� ��� ���� Ȯ��ǰ� ������
	{
		BossAwakeTime += deltaTime * speed;
		if (BossAwakeTime > 3)
		{
			Music::soundManager->PlayMusic(Music::eSoundList::BossAppear, Music::eSoundChannel::Boss);
			owner->FindObject<Image>("BossDialogue")->SetActive(true);
			isDialogueDelay = false;
			BossAwakeTime = 0;
			isBattleBegins = true;
		}
	}

	if (isBattleBegins == true) // ��� �� ������ �� ���� ����
	{
		BossAwakeTime += deltaTime * speed;
		if (BossAwakeTime > MaxDelayTime)
		{
			ResetPos();
			isBattleBegins = false;
		}
	}
}

void ProductionCamera::BossAwake(float deltaTime)
{
	auto& scale = transform->relativeScale;
	auto& loca = transform->relativeLocation;

	new DOTween(loca.x, EasingEffect::InSine, StepAnimation::StepOnceForward, 0.3f, loca.x, loca.x + 700);
	new DOTween(loca.y, EasingEffect::InSine, StepAnimation::StepOnceForward, 0.3f, loca.y, loca.y + 200);
	
	new DOTween(scale.x, EasingEffect::InSine, StepAnimation::StepOnceForward, 0.3f, 1, 0.6f);
	new DOTween(scale.y, EasingEffect::InSine, StepAnimation::StepOnceForward, 0.3f, 1, 0.6f);
	
	isDialogueDelay = true;
	timeManager->SetTimeScale(0.1);
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
			if (FindEnemy->enemyData.Type == "Boss")
			{ 
				owner->FindObject<Image>("BossDialogue")->SetActive(false);
				FindEnemy->isProduction = false;
				FindEnemy->isStoppage = true;
			}
			else
			{
				continue;
			}
		}
	}
	timeManager->SetTimeScale(TimeSave);
}

void ProductionCamera::Earthquake()
{
	Music::soundManager->PlayMusic(Music::eSoundList::BossWave, Music::eSoundChannel::BGM);
	auto& loca = transform->relativeLocation;
	auto& scale = transform->relativeScale;

	new DOTween(scale.x, EasingEffect::InSine, StepAnimation::StepOnceForward, 3.0f, 0.95f, 0.8f);
	new DOTween(scale.y, EasingEffect::InSine, StepAnimation::StepOnceForward, 3.0f, 0.95f, 0.8f);

	new DOTween(loca.x, EasingEffect::InOutBounce, StepAnimation::StepOnceForward, 3.0f, loca.x, loca.x + 220);
	new DOTween(loca.y, EasingEffect::InOutBounce, StepAnimation::StepOnceForward, 3.0f, loca.y, loca.y + 50);

	isEarthquake = true;
	TimeSave = timeManager->GetTimeScale();
}

void ProductionCamera::ReseEarthquake()
{
	auto& loca = transform->relativeLocation;
	auto& scale = transform->relativeScale;

	new DOTween(loca.x, EasingEffect::InOutBounce, StepAnimation::StepOnceForward, 2.5f, loca.x, loca.x - 220);
	new DOTween(loca.y, EasingEffect::InOutBounce, StepAnimation::StepOnceForward, 2.5f, loca.y, loca.y - 50);

	new DOTween(scale.x, EasingEffect::InSine, StepAnimation::StepOnceForward, 2.5f, 0.8f, 1.0f);
	new DOTween(scale.y, EasingEffect::InSine, StepAnimation::StepOnceForward, 2.5f, 0.8f, 1.0f);

	istest = true;
}

