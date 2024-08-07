#pragma once
#include "GameObject.h"
class IDamageNotify
{
public:
	virtual void Hit(float damage) = 0;  //데미지를 해당 오브젝트의 데미지를받는다? 해당오브젝트의 콜라이더? 일단 오브젝트로
};