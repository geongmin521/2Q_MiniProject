#pragma once
#include "GameObject.h"
class IDamageNotify
{
public:
	virtual void Hit(GameObject* obj) = 0;  //�������� �ش� ������Ʈ�� ���������޴´�? �ش������Ʈ�� �ݶ��̴�? �ϴ� ������Ʈ��
};