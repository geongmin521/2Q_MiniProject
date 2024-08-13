#pragma once

class Collider;
enum class CollisionLayer;
class CollisionManager //얘네도 싱글톤 베이스 상속받게 만들기
{
private:	
	static CollisionManager* inst;
	std::vector<Collider*> remove;
	std::map<CollisionLayer, std::vector<Collider*>>  colliders; //레이어랑 콜라이더 둘다 지우기? 
	std::set<std::pair<CollisionLayer, CollisionLayer>> collisonLayer; //레이어 들어간 놈들만 충돌할거임. 음... 이거는 생성자에서 처리하자. //이것들의 정의가 필요하면 헤더가 필요한데.. 
	//아니면 이것도 전방선언가능?
	void EraseCollider(Collider* col);
public:
	CollisionManager();
	~CollisionManager();
	static CollisionManager* GetInstance();
	void CollisionCheck();
	void Clear() {colliders.clear(); }
	void AddRemove(Collider* col);
	void pushCollider(Collider* col);//아 이것도 인라인 안됨.. 
};

