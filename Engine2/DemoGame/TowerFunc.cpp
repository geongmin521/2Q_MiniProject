#include "pch.h"
#include "TowerFunc.h"
#include "GameObject.h"
#include "Transform.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "Arrow.h"
#include "Pools.h"
void TowerFunc::FireBullet(GameObject* target, MathHelper::Vector2F pos,float id) //총알도 팩토리로 만들어야지.. //성수인지.. 화살인지 구분해서요청을 보내야하고... //지금까지 한거라도 머지해서.. 베지어 커브사용해서 총알 날릴까? 
{
	if (target != nullptr)
	{
		Arrow* arrow = dynamic_cast<Arrow*>(Pools::GetInstance().get()->PopPool(id + 500)); //총알은 아이디없긴한데.. //여기서 총알만 잘가져오면되겠지? 
		arrow->Init(pos, target);
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

void TowerFunc::MeleeAttack(GameObject* my,std::vector<GameObject*>& targets)
{
	for (auto& enemy : targets)
	{		
		EnemyBase* damageEnemy = dynamic_cast<EnemyBase*>(enemy); //타워에만 한정되지않을수도있으니까... 이것도 인터페이스로 뺄까?
		//계산기도 여기서 거치고 가야지.. 헬퍼에 세환님이 만들었으니까 유틸로 접근해서 적 타입이랑 같이 보내서 계산하면될듯?
		if (enemy != nullptr)
		{
			MathHelper::Vector2F dir = (enemy->GetWorldLocation() - my->GetWorldLocation()).Normalize();
			damageEnemy->Hit(Utility::CalCul("일반형", damageEnemy->enemyData.Type, 3),150);  //내타입은 어떻게넣지 일단 하드코딩 //데미지도
		}
	}
}
