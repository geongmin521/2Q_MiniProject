//#include "pch.h"
//#include "BoxCollider.h"
//#include "Bitmap.h"
//#include "Animation.h"
//#include "Transform.h"
//#include "D2DRenderer.h"
//#include "FiniteStateMachine.h"
//#include "TowerFsm.h"
//#include "AABB.h"
//#include "Music.h"
//#include "World.h" 
//#include "EnemyBase.h"
//#include "HolyTower.h"
//
//HolyTower::HolyTower(TowerData data) : TowerBase(data)
//{
//	towerData.name = "HolyTower";                    //csv���� �о�ͼ� �ٳ־����Բ� 
//	towerData.attackRange = 500.0f;
//	towerData.attackSpeed = 3.0f;
//	towerData.HP = 20000.0f;
//	curHP = towerData.HP;
//	SetBoundBox(0, 0, 500, 500); // ����Ÿ�� ���̴� �ڱ� ��üũ�⸸ŭ
//	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Ken")); //�ϴ� �� ���̾��� �������� �ִϸ��̼Ǹ� �ٸ���
//	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Tower));
//
//	FiniteStateMachine* fsm = new FiniteStateMachine();
//	AddComponent(fsm);
//	fsm->CreateState<TowerIdle>("Idle");
//	fsm->CreateState<TowerAttack>("Attack");
//	fsm->CreateState<TowerShared>("Shared");
//	fsm->CreateState<TowerDeath>("Death");
//	fsm->SetNextState("Idle");
//
//	renderOrder = 100;
//	transform->SetRelativeLocation({ 200,100 });
//}
//
//HolyTower::~HolyTower()
//{
//}
//
//void HolyTower::Update(float deltaTime)
//{
//	__super::Update(deltaTime);
//
//	FindTarget(GetComponent<BoxCollider>());
//}
//
//void HolyTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
//{
//	__super::Render(pRenderTarget);
//}
//
//void HolyTower::Attack(float deltaTime)
//{
//
//	//Arrow* arrow = new Arrow;
//	//arrow->owner = this->owner;
//	//arrow->Init(target, GetWorldLocation());
//	//owner->m_GameObjects.push_back(arrow);    //���� ���� ����
//}
//
//void HolyTower::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
//{
//}
//
//void HolyTower::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
//{
//}
//
//void HolyTower::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
//{
//}
//
