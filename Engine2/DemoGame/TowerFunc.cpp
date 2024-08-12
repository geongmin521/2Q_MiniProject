#include "pch.h"
#include "TowerFunc.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "circle.h"
#include "Transform.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "Arrow.h"
#include "Pools.h"

 void TowerFunc::FindTarget(CircleCollider& myCol,std::string tag, std::vector<GameObject*>& target) //단일 타겟 검색
{
	target.clear();
	GameObject* enemy = nullptr;
	
	TowerBase* myTower = dynamic_cast<TowerBase*>(myCol.owner);
	int minDistance = INT_MAX;
	for (auto& tragetCol : myCol.collideStatePrev) //콜라이더가 감지범위일거고.. 거기에 들어왔다면.. 그냥 그중에서 제일 가까운것만 찾으면됨
	{
		if (tragetCol->owner->name == tag && tragetCol->owner->isActive == true)
		{
			float distance = (myTower->GetWorldLocation() - tragetCol->owner->GetWorldLocation()).
			if (!(std::abs() <= myTower->towerData.attackRange * 50) //50곱하는건 지금 나중에 csv에서 한칸기준 수정?
				|| !(std::abs(myTower->GetWorldLocation().y - tragetCol->owner->GetWorldLocation().y) <= myTower->towerData.attackRange * 50))
				continue;      //적 본체위치가 사거리밖이면 넘어가게  이렇게맞나?
			float distance = myCol.circle->GetDistance(tragetCol->owner->transform->GetWorldLocation());
			if (distance < minDistance)
			{
				minDistance = distance;
				enemy = tragetCol->owner;
			}
		}			
	}
	if(enemy != nullptr)
		target.push_back(enemy);
}
 
void TowerFunc::FindTargets(CircleCollider& myCol, std::string tag, std::vector<GameObject*>& targets) //여러 타겟 검사하기
{
	targets.clear();
	TowerBase* myTower = dynamic_cast<TowerBase*>(myCol.owner);
	for (auto& tragetCol : myCol.collideStatePrev) //콜라이더가 감지범위일거고.. 거기에 들어왔다면.. 그냥 그중에서 제일 가까운것만 찾으면됨
	{
		
		if (tragetCol->owner->name == tag && tragetCol->owner->isActive == true)
		{
			if (!(std::abs(myTower->GetWorldLocation().x - tragetCol->owner->GetWorldLocation().x) <= myTower->towerData.attackRange * 50) //50곱하는건 지금 나중에 csv에서 한칸기준 수정?
				||!(std::abs(myTower->GetWorldLocation().y - tragetCol->owner->GetWorldLocation().y) <= myTower->towerData.attackRange * 50))
				continue;      //적 본체위치가 사거리밖이면 넘어가게  이렇게맞나?
			targets.push_back(tragetCol->owner);
		}
	}
}

void TowerFunc::FireBullet(GameObject* target, Vector2F pos) //총알도 팩토리로 만들어야지.. //성수인지.. 화살인지 구분해서요청을 보내야하고... //지금까지 한거라도 머지해서.. 베지어 커브사용해서 총알 날릴까? 
{
	if (target != nullptr)
	{
		Arrow* arrow = dynamic_cast<Arrow*>(Pools::GetInstance().get()->PopPool(500)); //총알은 아이디없긴한데.. //여기서 총알만 잘가져오면되겠지? 
		arrow->Init(target, pos);
	}
}

void TowerFunc::Heal(std::vector<GameObject*>& targets) //게임오브젝트의 벡터를 가져와서 이름으로 계산하기.. //어차피 태그로 잘 타겟을 잘 찾았을테니까. 
{
	for (auto& tower : targets)
	{
		TowerBase* healTower = dynamic_cast<TowerBase*>(tower); //타워에만 한정되지않을수도있으니까... 이것도 인터페이스로 뺄까?
		if(tower != nullptr) 
			healTower->Heal(1000);
	}
}

void TowerFunc::MeleeAttack(std::vector<GameObject*>& targets)
{
	for (auto& enemy : targets)
	{		
		EnemyBase* damageEnemy = dynamic_cast<EnemyBase*>(enemy); //타워에만 한정되지않을수도있으니까... 이것도 인터페이스로 뺄까?
		//계산기도 여기서 거치고 가야지.. 헬퍼에 세환님이 만들었으니까 유틸로 접근해서 적 타입이랑 같이 보내서 계산하면될듯?
		if (enemy != nullptr)
			damageEnemy->Hit(40);
	}
}
