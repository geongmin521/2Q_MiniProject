#pragma once
class GameObject;
class CircleCollider;
class MathHelper::Vector2F;
class TowerFunc //Ÿ���� �������ִ� �ɷµ� //�ν��Ͻ��� �����ʿ䰡�ֳ�? 
{
public:

	static void FindTarget(CircleCollider& myCol, std::string tag, std::vector<GameObject*>& target); //����� ���� �Լ������ �����̱⶧����.. staticŰ����� �����
	static void FindTargets(CircleCollider& myCol,  std::string tag, std::vector<GameObject*>& targets);
	static void FireBullet(GameObject* target, MathHelper::Vector2F pos);
	static void Heal(std::vector<GameObject*>& targets);
	static void MeleeAttack(std::vector<GameObject*>& targets); //��������
};

