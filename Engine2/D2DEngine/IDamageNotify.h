#pragma once
#include "GameObject.h"

class IDamageNotify
{
public:

	virtual void Hit(float damage) = 0;  //데미지를 공격자가 계산해서 넣어줘야함
	virtual void Heal(float heal) = 0; //데미지랑 같이쓸려했는대 일단 추가
	virtual ~IDamageNotify() = default;
};