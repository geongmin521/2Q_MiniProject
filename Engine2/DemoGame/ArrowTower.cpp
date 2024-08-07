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

ArrowTower::ArrowTower(TowerData data) : TowerBase(data)
{
	SetBoundBox(0, 0, 102, 82);
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Ken"));

	//towerData.name = "ArrowTower";                    //csv���� �о�ͼ� �ٳ־����Բ� 
	//towerData.attackRange = 300.0f;
	//towerData.attackSpeed = 1.0f;
	//towerData.HP = 200.0f;
	attackRange = new AABB;
	attackRange->SetExtent(towerData.attackRange, towerData.attackRange);
	//�̹����� ��������.. �ڵ����� ȸ���� �߽���ǥ�� �����ϱ�.. 
	BoxCollider* attack;
	box = CreateComponent<BoxCollider>();
	box->aabb = attackRange;
	box->SetCollisionType(CollisionType::Overlap);
	box->SetCollisionLayer(CollisionLayer::Tower);
	box->SetNotify(this);
	box->PushCollider();
	box->name = "attackbox";
	//AddComponent(new BoxCollider(attackRange,CollisionType::Overlap, this, CollisionLayer::Tower));
	AddComponent(new BoxCollider(boundBox ,CollisionType::Block, this, CollisionLayer::Tower));
	//GetComponent<CircleCollider>()->SetOnStay(true);
	//�ڽ��� ������ �پ��� ���� ��ġ�� ȸ���ϴµ� �ֱ׷���>? 
	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared"); 
	fsm->CreateState<TowerDeath>("Death");


	fsm->SetNextState("Idle");                    //���̾�� �ϴ� attack�� �׽�Ʈ 
	
	renderOrder = 100;
	transform->SetRelativeLocation({200,200});

	// test
	test.SetBoxSize(300, 100);
	test.SetPos(20, 20);
	test.LoadFont(L"Calibri");
	test.CreateLayoutText(L"��Ʈ �׽�Ʈ�Դϴ�.");
	test.Sort(Setting::RIGHT);
	test.SetFontLocation(Setting::BOTTOM);
	test.SetSize(50.f, {2, 4});
	test.OnTransform();
	test.GetTransform()->SetParent(transform);
}

ArrowTower::~ArrowTower()
{
}

void ArrowTower::Update(float deltaTime)
{
	__super::Update(deltaTime);
	//attackRange->SetCenter(boundBox->Center.x + towerData.attackRange, boundBox->Center.y);
	//Music::soundManager->GetInstance()->PlayMusic();

}

void ArrowTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	// test
	test.DrawFont(D2D1::ColorF(D2D1::ColorF::Black));


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


void ArrowTower::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
	std::cout << "test";
	
}

void ArrowTower::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	if (otherComponent->getActive())
	{
		if (ownedComponent->name == "attackbox" && otherComponent->owner->name == "Enemy") //���ùڽ��� ������� �����ʿ�
		{

			objs.push_back(otherComponent->owner);
			std::cout << "������";
		}
	}

	//if()  //������ >> enemy 
	//Hit(otherComponent->owner);
}


void ArrowTower::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	std::cout << "�� �浹��";
}

void ArrowTower::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	if (otherComponent->owner->name == "Enemy" && !objs.empty())
	objs.erase(std::remove(objs.begin(),objs.end(),otherComponent->owner));
}

void ArrowTower::Hit(GameObject* obj)
{
	EnemyBase* enemy;
	enemy = dynamic_cast<EnemyBase*>(obj);
	towerData.HP -= enemy->enemyData.ATK;
	std::cout << std::endl << towerData.HP << std::endl;
}
