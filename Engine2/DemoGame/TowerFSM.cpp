#include "pch.h"
#include "TowerBase.h"
#include "TowerFsm.h"
#include "FiniteStateMachine.h"
#include "World.h"
#include "Animation.h"
#include "Transform.h"
#include "Pools.h"
#include "EnemyBase.h"
#include "GameManager.h"
#include "Container.h"
#include "Music.h"

TowerFSM::TowerFSM(FiniteStateMachine* pOwner, std::string Name) : FSMState(pOwner, Name)
{
	tower = (TowerBase*)owner->owner;
	ani = owner->owner->GetComponent<Animation>();
}
TowerFSM::~TowerFSM()
{

}

TowerShared::TowerShared(FiniteStateMachine* pOwner, std::string Name) : TowerFSM(pOwner, Name)
{
	owner->SetSharedTransition(this);
}

void TowerShared::EnterState()
{
}

void TowerShared::Update(float DeltaTime)
{
	if(tower->curHP <= 0)
	{
		owner->SetNextState("Death");
	}
}

void TowerShared::ExitState()
{
}

void TowerIdle::EnterState()
{
	if(ani != nullptr)
	ani->SetAnimation(0, false);
}

void TowerIdle::Update(float DeltaTime) //타겟으로 본인도 들어오나? 타겟은 등록된 태그만 먹게해놨는데.. 
{
	tower->Search();
	if (tower->target.empty() == false && gameManager->isBattle == true)
	{
		tower->cooldown += DeltaTime;

		if (tower->cooldown > tower->curSpeed)
		{
			tower->cooldown = 0;
			owner->SetNextState("Attack");
		}	
	}
	//else
	//{
	//	cooldown = tower->towerData.attackSpeed; //첫 사거리에 들어온 적에게는 딜레이없이 쏘기위함.. //
	//}
}

void TowerIdle::ExitState()
{
}

void TowerAttack::EnterState()
{
	doubleTime = 0.1f;
	attackcount = 0;
	if (ani != nullptr)
	ani->SetAnimation(1, false,false);
	std::string str = tower->towerData.Type + "Attack";
	Music::soundManager->PlayMusic(Music::soundManager->toEnum(str), Music::eSoundChannel::TowerAttack);
	
}


void TowerAttack::Update(float DeltaTime) //공속이 애니메이션보다 빨라지면.. 공속이 느려지는 잠재적인 버그가능.. 애니메이션속도가 공속이랑 같아지도록 세팅하는거 만들기.. 
{
	if ((ani != nullptr && ani->IsEnd()) || ani == nullptr )  //말뚝타워는 애니메이션이없이 비트맵이라 추가
	{
		if (tower->towerData.ability == "double")
		{
			doubleTime += DeltaTime;
			if (doubleTime > 0.15f)
			{
				tower->Attack(DeltaTime);
				attackcount++;
				doubleTime = 0;
			}
			if (attackcount == 2)
			{
				owner->SetNextState("Idle");
			}
		}
		else
		{
			tower->Attack(DeltaTime);
			owner->SetNextState("Idle");
		}
	}
}

void TowerAttack::ExitState()
{
	std::string str = tower->towerData.Type + "Effect";
	Music::soundManager->PlayMusic(Music::soundManager->toEnum(str), Music::eSoundChannel::TowerEffect);
}

void TowerDeath::EnterState()
{
	tower->hitEffct = false;
	tower->container->Clear();
	if (ani != nullptr)
	ani->SetAnimation(2, false,false); 
}

void TowerDeath::Update(float DeltaTime)
{
	if ((ani != nullptr && ani->IsEnd()) || ani == nullptr)
	{
		Pools::GetInstance().get()->AddPool(tower);
	}
	
}

void TowerDeath::ExitState()
{
}
