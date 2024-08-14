#pragma once
#include "GameObject.h"

class IDamageNotify
{
public:

	virtual void Hit(float damage, float knockback = 0) = 0;  //�������� �����ڰ� ����ؼ� �־������ 
	virtual void Heal(float heal) = 0; //�������� ���̾����ߴ´� �ϴ� �߰�
	virtual ~IDamageNotify() = default;
};