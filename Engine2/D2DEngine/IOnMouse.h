#pragma once
class IOnMouse
{
public:
	virtual void OnMouse() = 0; //������Ʈ���� ���콺�� �ö���� �ѹ�ȣ�� 
	virtual void StayMouse() = 0; //������Ʈ���� ���콺�� �ö�����̸�
	virtual void OutMouse() = 0; // ���콺�� ������Ʈ���� ������ ȣ��
};