#pragma once
class GameObject;
class CircleCollider;
class TowerFunc //Ÿ���� �������ִ� �ɷµ� //�ν��Ͻ��� �����ʿ䰡�ֳ�? 
{
public:
	static void FindTarget(CircleCollider& myCol, std::string tag, std::vector<GameObject*>& target); //����� ���� �Լ������ �����̱⶧����.. staticŰ����� �����
	static void FindTargets(CircleCollider& myCol,  std::string tag, std::vector<GameObject*>& targets);
	static void FireBullet(GameObject* target);
	static void Heal(std::vector<GameObject*>& targets);
	static void MeleeAttack(std::vector<GameObject*>& targets); //��������
};

