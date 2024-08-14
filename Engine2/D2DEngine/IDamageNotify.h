#pragma once
#include "GameObject.h"

class IDamageNotify
{
public:

	virtual void Hit(float damage, float knockback = 0) = 0;
	virtual void Heal(float heal) = 0; 
	virtual ~IDamageNotify() = default;
};