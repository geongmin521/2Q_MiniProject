#pragma once
#include "GameObject.h"
class IDamageNotify
{
public:
	virtual void Hit(float damage) = 0;  //�������� �ش� ������Ʈ�� ���������޴´�? �ش������Ʈ�� �ݶ��̴�? �ϴ� ������Ʈ��
};