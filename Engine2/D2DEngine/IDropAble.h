#pragma once
class UI;
class IDropAble
{
public:
	virtual void OnDrop(UI* ui) = 0; //�巡�� ���̺� ������Ʈ�� endDrag�� ȣ��ɶ� �̰� ȣ��
};
