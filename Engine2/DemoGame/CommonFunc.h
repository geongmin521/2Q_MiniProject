#pragma once
class GameObject;
class CircleCollider;
class MathHelper::Vector2F;

class CommonFunc 
{
public:
	static void FindTarget(CircleCollider& myCol, std::string tag, std::vector<GameObject*>& target, float Range); 
	static void FindTargets(CircleCollider& myCol, std::string tag, std::vector<GameObject*>& targets, float Range);
};

