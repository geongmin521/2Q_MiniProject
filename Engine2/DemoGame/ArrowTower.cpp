#include "../D2DEngine/pch.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/CircleCollider.h"
#include "../D2DEngine/Circle.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "TowerFsm.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/Music.h"
#include "../D2DEngine/World.h" 
#include "EnemyBase.h"
#include "ArrowTower.h"

ArrowTower::ArrowTower()
{
	towerData.name = "ArrowTower";                    //csv���� �о�ͼ� �ٳ־����Բ� 
	towerData.attackRange = 300.0f;
	towerData.attackSpeed = 1.0f;
	towerData.HP = 200.0f;

	SetBoundBox(0, 0, towerData.attackRange, towerData.attackRange);
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Ken"));
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Tower));

	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared"); 
	fsm->CreateState<TowerDeath>("Death");
	fsm->SetNextState("Idle");                    //���̾�� �ϴ� attack�� �׽�Ʈ 
	
	renderOrder = 100;
	transform->SetRelativeLocation({200,200});

	//attackRange = new AABB;
	//attackRange->SetExtent(towerData.attackRange, towerData.attackRange);
	////�̹����� ��������.. �ڵ����� ȸ���� �߽���ǥ�� �����ϱ�.. 
	////BoxCollider* attack;
	//searchBound = CreateComponent<BoxCollider>();
	//searchBound->Init(attackRange, CollisionType::Overlap, this, CollisionLayer::Tower);
	//searchBound->name = "attackbox";
	////GetComponent<>
	//BoxCollider* bound = new BoxCollider(boundBox, CollisionType::Block, this, CollisionLayer::Tower);
	//AddComponent(bound);
	//towerBound = CreateComponent<BoxCollider>();
	////towerBound->Init();
	////towerBound->name = "tower";
	////AddComponent(new BoxCollider(attackRange,CollisionType::Overlap, this, CollisionLayer::Tower));
	////AddComponent(new BoxCollider(boundBox ,CollisionType::Block, this, CollisionLayer::Tower));
	//

}

ArrowTower::~ArrowTower()
{
}

void ArrowTower::Update(float deltaTime)
{

	__super::Update(deltaTime);
	//attackRange->SetCenter(boundBox->Center.x + towerData.attackRange, boundBox->Center.y);
	//Music::soundManager->GetInstance()->PlayMusic();

	//target�� ���� ������
	//GetComponent<BoxCollider>()->collideStateCurr.begin() it;
	//it = owner name enemy;
	//Getwroldlocation  �Ÿ���
	//	>> ���������� Ÿ������
	//	�갡 ������ target null �ƴϸ� Ÿ��;
	if (target == nullptr)
	{
		Find();
	}

}
void ArrowTower::Find()
{
	std::vector<GameObject*> enemys;
	for (auto& col : GetComponent<BoxCollider>()->collideStatePrev)
	{
		if (col->owner->name == "Enemy")
			enemys.push_back(col->owner);
	}
	float min = 1000;
	float curMin;
	float xDistance;
	float yDistance;
	GameObject* curTarget = nullptr;
	if (!enemys.empty())
	{
		for (auto& enemy : enemys)
		{
			std::cout << " �� ����";
			xDistance = (GetWorldLocation().x - enemy->GetWorldLocation().x);
			//if (xDistance > 0) continue; //�ϴ� Ÿ���ڷΰ��� ���ݸ��ϰ�
			yDistance = std::abs(GetWorldLocation().y - enemy->GetWorldLocation().y);
			curMin = std::min(xDistance, yDistance);

			if (min > curMin)
				min = curMin;

			curTarget = enemy;
		}
	}
	if (curTarget != nullptr)
		target = curTarget;
}

void ArrowTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);

	//GetComponent<BoxCollider>()->aabb->Center = { 300,300 };
	
}

void ArrowTower::Attack(float deltaTime)
{ 
	
	Arrow* arrow = new Arrow;
	arrow->owner = this->owner;
	Vector2F dir  = Vector2F(target->GetWorldLocation()) - Vector2F(GetWorldLocation());
	dir.Normalize();
	arrow->Init({ dir }, GetWorldLocation());
	owner->m_GameObjects.push_back(arrow);
}

//���� Ȯ���ϰ� ������ ȯ���� �������Ѵ�. 

void ArrowTower::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
	std::cout << "test";
}

void ArrowTower::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	//ownedComponent.get
	//if (otherComponent->getActive())
	//{
	//	if (ownedComponent->name == "attackbox" && otherComponent->owner->name == "Enemy") 
	//	{
	//		objs.push_back(otherComponent->owner); //
	//		std::cout << "������";
	//	}
	//}
}


void ArrowTower::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	std::cout << "�� �浹��";
}

void ArrowTower::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	/*if (otherComponent->owner->name == "Enemy" && !objs.empty())
		objs.erase(std::remove(objs.begin(),objs.end(),otherComponent->owner));*/
}

void ArrowTower::Hit(GameObject* obj)
{
	EnemyBase* enemy;
	enemy = dynamic_cast<EnemyBase*>(obj);
	towerData.HP -= enemy->enemyData.ATK;
	std::cout << std::endl << towerData.HP << std::endl;
}
