#include "pch.h"
#include "BoxCollider.h"
#include "Bitmap.h"
#include "Animation.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "AABB.h"
#include "Music.h"
#include "Utility.h"
#include "EnemyBase.h"
#include "..//D2DEngine/BezierMovement.h"
#include "Arrow.h"

Arrow::Arrow()
{
	SetBoundBox(0, 0, 40, 36);
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Arrow"));
	renderOrder = 100;
}

Arrow::~Arrow()
{
}



void Arrow::Init(GameObject* target, MathHelper::Vector2F location)
{
	this->target = target;
	transform->SetRelativeLocation({ location.x + 50.0f,location.y - 20.f });

	AddComponent(new BezierMovement(transform, speed,target));
	
}

void Arrow::Update(float deltaTime)
{
	__super::Update(deltaTime);

	
	if (target->isActive == true)
	{
		 //아직 못맞췄을때 사라질경우 처리할곳 maybe
	}
	else
	{
		isActive = false;
	}

	if (std::abs(target->GetWorldLocation().x - GetWorldLocation().x) <= 1.0f &&
		std::abs(target->GetWorldLocation().y - GetWorldLocation().y) <= 1.0f)
	{
		EnemyBase* enemy = dynamic_cast<EnemyBase*>(target);

		
		enemy->Hit(Utility::CalCul("석궁형",enemy->enemyData.Type,5000));
		//
		isActive = false;
	}

}


void Arrow::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}


