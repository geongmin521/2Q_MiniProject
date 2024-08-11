#pragma once
#include "Data.h"
#include <typeindex>

using namespace std;
using namespace MathHelper;

class World;
class GameObject;

class Factory 
{
private:
	GameObject* object;
public:
	Factory();
	~Factory();

	template<typename T, typename... Args>
	Factory& createObj(Args&&... args) {
		object = new T(std::forward<Args>(args)...); 
		return *this;
	} 
	template<typename T> //�̰� ���ø��̶� Ÿ���� �ѹ�������ϴ°� �� �����ϳ�... 
		T* Get() {
		return dynamic_cast<T*>(object);
	}
	void InsertWorld(GameObject* obj);
	Factory& setPosition(Vector2F pos);
	Factory& setScale(Vector2F sclae);
	Factory& setRoot(std::vector<GameObject*>* Root); 
	Factory& setIsActive(bool active); 
	void build() { InsertWorld(object); } //�Ҹ��ڿ��� �ڵ�ȣ��Ǹ� ���忡 ����ֱ�

	//�ᱹ Ÿ���� ���� �ָ�Ǵ°ǵ�.. �׷� pool���� �޾ƿö��뵵. ���ø�����? �ƴϸ� Ÿ�Ծ��̵��? �޾ƿ͵� �ɰŰ�����? 
};
