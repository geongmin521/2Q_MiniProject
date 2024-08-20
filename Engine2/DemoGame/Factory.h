#pragma once
#include "Data.h"
#include "GameObject.h" //상호참조 오류안나나? 
#include <typeindex>

#define Make(type) Factory().createObj<type> //축약형

using namespace std;
using namespace MathHelper;

class World;
class GameObject;
class Transform;
class D2DFont;
class Component;
class Factory 
{
private:
	GameObject* object;
public:
	Factory();
	~Factory();

	template<typename T, typename... Args>
	Factory& createObj(Args&&... args) { //생성에 필요한 아이디를 예만 알았으면좋겠는데.. 
		object = new T(std::forward<Args>(args)...); 
		return *this;
	} 
	template<typename T>
	T* Get() {
		T* result = dynamic_cast<T*>(object);
		assert(result && "Dynamic cast failed");
		return result;
	}
	template<typename T>
	void Get(T*& container) {
		container = dynamic_cast<T*>(object);
		assert(container && "Dynamic cast failed");
	}
	template<typename T>
	void Get(std::vector<T*>& container) {
		T* result = dynamic_cast<T*>(object);
		assert(result && "Dynamic cast failed");
		container.push_back(result);
	}
	template<typename T>
	void GetComponent(T*& container) {
		container = object->GetComponent<T>(); //아 얘가 몰라서그런가>? 
		assert(container && "GetComponent failed");
	}

	GameObject* Get() { return object; } //기본형
	void InsertWorld(GameObject* obj);
	Factory& setPosition(Vector2F pos);
	Factory& setPos_Parent(Vector2F pos, Transform* parent); //많이쓰이는 애들의 축약형
	Factory& setPos_Parent_Text(Vector2F pos, Transform* parent, std::wstring text, int size);
	Factory& setScale(Vector2F sclae);
	Factory& setParent(Transform* parent);
	Factory& setRoot(std::vector<GameObject*>* Root); 
	Factory& setActive(bool active); 
	Factory& setRenderOrder(int order); 
	Factory& AddText(std::wstring text, int size, int posx=0, int posy=0, D2DFont** fontcomponent = nullptr);
	Factory& AddComponent(Component* pComponent);
	void build() { InsertWorld(object); }
};
