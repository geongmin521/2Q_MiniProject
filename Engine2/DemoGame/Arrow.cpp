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
#include "../D2DEngine/BezierMovement.h"
#include "Arrow.h"

Arrow::Arrow( float speed, std::wstring imagePath) //총알도 애니메이션 있는건가?그냥 이미지면 되는게 아닌가? 일단은 그냥 비트맵으로 해볼까? 
{
	SetBoundBox(0, 0, 40, 36);
	AddComponent(new Bitmap(L"..\\Data\\Image\\" + imagePath));
	//AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Arrow"));
	renderOrder = 100;
	AddComponent(new BezierMovement(transform, speed)); //발사되는순간에 적의 위치를 받아오는게 맞지.. 
}

Arrow::~Arrow()
{
}

void Arrow::Init(GameObject* target, MathHelper::Vector2F location)
{
	this->target = target;
	this->transform->SetRelativeLocation(location);
	GetComponent<BezierMovement>()->target = target;
}

void Arrow::Update(float deltaTime)
{
	__super::Update(deltaTime);
	if (std::abs(target->GetWorldLocation().x - GetWorldLocation().x) <= 1.0f &&
		std::abs(target->GetWorldLocation().y - GetWorldLocation().y) <= 1.0f)
	{
		EnemyBase* enemy = dynamic_cast<EnemyBase*>(target);		//아 이걸 적으로 다이나믹 캐스트를하는구나.. 노티피를 들고있는방식으로갈까? 
		enemy->Hit(Utility::CalCul("석궁형",enemy->enemyData.Type, 30));
		SetActive(false);
	}

}

void Arrow::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}


