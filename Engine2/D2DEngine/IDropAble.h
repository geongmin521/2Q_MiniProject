#pragma once
class UI;
class IDropAble
{
public:
	virtual void OnDrop(GameObject* ui) = 0; //drag������Ʈ�� enddrag�� ȣ��ɶ� ȣ��
	virtual ~IDropAble() = default;
};
