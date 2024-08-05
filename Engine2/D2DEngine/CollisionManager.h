#pragma once

class Collider;
enum class CollisionLayer;
class CollisionManager
{
private:
	CollisionManager();
	~CollisionManager();
	static CollisionManager* inst;
	std::map<CollisionLayer, std::vector<Collider*>>  colliders;
	std::set<std::pair<CollisionLayer, CollisionLayer>> collisonLayer; //레이어 들어간 놈들만 충돌할거임. 음... 이거는 생성자에서 처리하자. //이것들의 정의가 필요하면 헤더가 필요한데.. 
	//아니면 이것도 전방선언가능?
public:
	static CollisionManager* GetInstance();
	void CollisionCheck();
	void EraseCollider(Collider* col);
	void pushCollider(Collider* col);//아 이것도 인라인 안됨.. 
};

