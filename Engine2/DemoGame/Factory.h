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
	template<typename T> 
		T* Get() { 
		return dynamic_cast<T*>(object);
	}
	GameObject* Get() { return object; } //±âº»Çü
	void InsertWorld(GameObject* obj);
	Factory& setPosition(Vector2F pos);
	Factory& setScale(Vector2F sclae);
	Factory& setParent(Transform* parent);
	Factory& setRoot(std::vector<GameObject*>* Root); 
	Factory& setActive(bool active); 
	Factory& setRenderOrder(int order); 
	Factory& AddText(std::wstring text, int size, int posx=0, int posy=0);
	void build() { InsertWorld(object); }
};
