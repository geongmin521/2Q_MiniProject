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
//	towerData.name = "HolyTower";                    //csv에서 읽어와서 다넣어지게끔 
//	towerData.attackRange = 500.0f;
//	towerData.attackSpeed = 3.0f;
//	towerData.HP = 20000.0f;
//	curHP = towerData.HP;
//	SetBoundBox(0, 0, 500, 500); // 근접타워 높이는 자기 몸체크기만큼
//	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Ken")); //일단 켄 같이쓰고 근접공격 애니메이션만 다르게
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
//	//owner->m_GameObjects.push_back(arrow);    //성수 만들어서 생성
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
