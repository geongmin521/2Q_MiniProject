#pragma once
#include "Data.h"
#include <typeindex>

using namespace std;
using namespace MathHelper;

class World;
class GameObject;
class Transform;

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
		T* Get() { //이왕 이렇게 된거.. 컴포넌트 베이스인지.. 게임오브젝트 베이스인지로 분리해서 가져오는것도 가능하지않나?
		return dynamic_cast<T*>(object);
	}
	GameObject* Get() { return object; } //기본형
	void InsertWorld(GameObject* obj);
	Factory& setPosition(Vector2F pos);
	Factory& setScale(Vector2F sclae);
	Factory& setParent(Transform* parent);
	Factory& setRoot(std::vector<GameObject*>* Root); 
	Factory& setActive(bool active); 
	Factory& setRenderOrder(int order); 
	Factory& AddText(std::wstring text, int size, int posx=0, int posy=0);
	void build() { InsertWorld(object); } //소멸자에서 자동호출되며 월드에 집어넣기
};
