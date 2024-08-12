#pragma once
class GameObject;
class CircleCollider;
class MathHelper::Vector2F;

class CommonFunc //타워랑 적들 모두 공유하는 기능을 모아놓은클래스
{
public:
	static void FindTarget(CircleCollider& myCol, std::string tag, std::vector<GameObject*>& target, float Range); //멤버가 없는 함수기능의 모임이기때문에.. static키워드로 만든다
	static void FindTargets(CircleCollider& myCol, std::string tag, std::vector<GameObject*>& targets, float Range);
};

