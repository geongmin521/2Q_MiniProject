#include "pch.h"
#include "EnemyFunc.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "IDamageNotify.h"
#include "Arrow.h"

void EnemyFunc::NormalAttack(GameObject* target, float Damage) //�̰��� ��� �����������������.. 
{
	IDamageNotify* nofity = dynamic_cast<IDamageNotify*>(target);
	nofity->Hit(Damage);
}

void EnemyFunc::BombAttack(EnemyBase* origin, GameObject* target, float Damage) //Ÿ���� �ƿ� ã�������� ���̳��� ĳ��Ʈ���ؼ� ������
{
	IDamageNotify* nofity = dynamic_cast<IDamageNotify*>(target);
	nofity->Hit(Damage);
	//�Ƹ� ����Ʈ�� �Ѹ��� ������ ������Ǵµ�... 
	origin->curHP = 0;
}

void EnemyFunc::RangedAttack(GameObject* target,MathHelper::Vector2F pos, float Damage) //�Ѿ��� ���θ��� ���ɰŰ�.. 
{
	Arrow* arrow = new Arrow(0.3f, L"vampire.png");
	arrow->Init(target, pos);
}
