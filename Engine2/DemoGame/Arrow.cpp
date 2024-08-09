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

Arrow::Arrow( float speed, std::wstring imagePath) //�Ѿ˵� �ִϸ��̼� �ִ°ǰ�?�׳� �̹����� �Ǵ°� �ƴѰ�? �ϴ��� �׳� ��Ʈ������ �غ���? 
{
	SetBoundBox(0, 0, 40, 36);
	AddComponent(new Bitmap(imagePath));//L"..\\Data\\Image\\Crossbow.png"
	//AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Arrow"));
	renderOrder = 100;
	AddComponent(new BezierMovement(transform, speed)); //�߻�Ǵ¼����� ���� ��ġ�� �޾ƿ��°� ����.. 
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

	
	if (target->isActive == true)
	{
		 //���� ���������� �������� ó���Ұ� maybe
	}
	else
	{
		isActive = false;
	}

	if (std::abs(target->GetWorldLocation().x - GetWorldLocation().x) <= 1.0f &&
		std::abs(target->GetWorldLocation().y - GetWorldLocation().y) <= 1.0f)
	{
		EnemyBase* enemy = dynamic_cast<EnemyBase*>(target);		
		enemy->Hit(Utility::CalCul("������",enemy->enemyData.Type,5000));
		//
		isActive = false;
	}

}


void Arrow::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}


