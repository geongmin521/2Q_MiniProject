#pragma once

class Collider;
enum class CollisionLayer;
class CollisionManager
{
private:

	CollisionManager();
	~CollisionManager();
	static CollisionManager* inst;
	std::vector<Collider*> remove;
	std::map<CollisionLayer, std::vector<Collider*>>  colliders;
	std::set<std::pair<CollisionLayer, CollisionLayer>> collisonLayer; //���̾� �� ��鸸 �浹�Ұ���. ��... �̰Ŵ� �����ڿ��� ó������. //�̰͵��� ���ǰ� �ʿ��ϸ� ����� �ʿ��ѵ�.. 
	//�ƴϸ� �̰͵� ���漱�𰡴�?
	void EraseCollider(Collider* col);
public:
	static CollisionManager* GetInstance();
	void CollisionCheck();
	void AddRemove(Collider* col);
	void pushCollider(Collider* col);//�� �̰͵� �ζ��� �ȵ�.. 
};

