#pragma once
class UI;
class IDropAble
{
public:
	virtual void OnDrop(GameObject* ui) = 0; //�巡�� ���̺� ������Ʈ�� endDrag�� ȣ��ɶ� �̰� ȣ��
	virtual ~IDropAble() = default;
};
