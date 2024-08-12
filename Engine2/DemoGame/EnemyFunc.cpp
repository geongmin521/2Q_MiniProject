#include "pch.h"
#include "EnemyFunc.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "Arrow.h"

void EnemyFunc::NormalAttack(TowerBase* target, float Damage)
{
	target->Hit(Damage);
}

void EnemyFunc::BombAttack(EnemyBase* origin,TowerBase* target, float Damage) //Ÿ���� �ƿ� ã�������� ���̳��� ĳ��Ʈ���ؼ� ������
{
	target->Hit(Damage);
	//�Ƹ� ����Ʈ�� �Ѹ��� ������ ������Ǵµ�... 
	origin->curHP = 0;
}

void EnemyFunc::RangedAttack(TowerBase* target,MathHelper::Vector2F pos, float Damage) //�Ѿ��� ���θ��� ���ɰŰ�.. 
{
	Arrow* arrow = new Arrow(0.3f, L"vampire.png");
	arrow->Init(target, pos);
}
