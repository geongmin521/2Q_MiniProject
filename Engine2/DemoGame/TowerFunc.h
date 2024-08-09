#pragma once
class GameObject;
class CircleCollider;
class TowerFunc //타워가 가질수있는 능력들 //인스턴스를 가질필요가있나? 
{
public:
	static void FindTarget(CircleCollider& myCol, std::string tag, std::vector<GameObject*>& target); //멤버가 없는 함수기능의 모임이기때문에.. static키워드로 만든다
	static void FindTargets(CircleCollider& myCol,  std::string tag, std::vector<GameObject*>& targets);
	static void FireBullet(GameObject* target);
	static void Heal(std::vector<GameObject*>& targets);
	static void MeleeAttack(std::vector<GameObject*>& targets); //근접공격
};

