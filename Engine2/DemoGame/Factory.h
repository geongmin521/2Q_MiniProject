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
	template<typename T> //이게 템플릿이라 타입을 한번더써야하는게 좀 불편하네... 
		T* Get() {
		return dynamic_cast<T*>(object);
	}
	void InsertWorld(GameObject* obj);
	Factory& setPosition(Vector2F pos);
	Factory& setScale(Vector2F sclae);
	Factory& setRoot(std::vector<GameObject*>* Root); 
	Factory& setIsActive(bool active); 
	void build() { InsertWorld(object); } //소멸자에서 자동호출되며 월드에 집어넣기

	//결국 타워만 만들어서 주면되는건데.. 그럼 pool에서 받아올때대도. 템플릿으로? 아니면 타입아이디로? 받아와도 될거같은데? 
};
