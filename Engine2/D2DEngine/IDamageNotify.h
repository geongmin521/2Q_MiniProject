#pragma once
#include "GameObject.h"

class IDamageNotify
{
public:

	virtual void Hit(float damage) = 0; 
	virtual void Heal(float heal) = 0; 
	virtual ~IDamageNotify() = default;
};