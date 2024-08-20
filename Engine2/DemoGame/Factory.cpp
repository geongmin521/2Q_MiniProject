#include "pch.h"
#include "Factory.h"
#include "DataManager.h"
#include "Transform.h"
#include "World.h"
#include "SceneManager.h"
#include "D2DFont.h"
#include "Bitmap.h"

Factory::Factory() 
{
}

Factory::~Factory()
{
    build();
}


Factory& Factory::setPosition(Vector2F pos) {
    object->transform->SetRelativeLocation(pos);
    return *this;
}

Factory& Factory::setPos_Parent(Vector2F pos, Transform* parent)
{
    setPosition(pos);
    setParent(parent);
    return *this;
}

Factory& Factory::setPos_Parent_Text(Vector2F pos, Transform* parent, std::wstring text, int size)
{
    setPosition(pos);
    setParent(parent);
    AddText(text, size);
    return *this;
}

Factory& Factory::setScale(Vector2F scale) {
    object->transform->SetRelativeScale(scale);
    return *this;
}

Factory& Factory::setParent(Transform* parent)
{
    object->renderOrder = parent->owner->renderOrder + 1; 
    object->transform->SetParent(parent);
    return *this;
}

Factory& Factory::setRoot(std::vector<GameObject*>* Root) 
{
    Root->push_back(object);
    return *this;
}

Factory& Factory::setActive(bool active)
{
    object->SetActive(active);
    return *this;
}

Factory& Factory::setRenderOrder(int order)
{
    object->renderOrder = order;
    return *this;
}

Factory& Factory::AddText(std::wstring text, int size, int posx,int posy, D2DFont** fontcomponent)
{
    D2DFont* Text = new D2DFont(text); 
    object->AddComponent(Text);
    Bitmap* bitmap = object->GetComponent<Bitmap>();
    if(bitmap != nullptr)
        Text->SetBoxSize(bitmap->GetSize()); 
    Text->SetSize(size, { 0,(unsigned int)text.size() });
    Text->SetPos(posx, posy);
    if (fontcomponent != nullptr)
        *fontcomponent = Text;
    return *this;
}

Factory& Factory::AddComponent(Component* pComponent)
{ 
    pComponent->SetOwner(object);
    object->ownedComponents.push_back(pComponent);
    return *this;
}


void Factory::InsertWorld(GameObject* obj)
{
    World* curWorld = SceneManager::GetInstance().get()->GetCurWorld();
    obj->SetOwner(curWorld);
    for (auto it = curWorld->m_GameObjects.begin(); it != curWorld->m_GameObjects.end(); it++)
    {
        if ((*it)->renderOrder > obj->renderOrder)
        {
            curWorld->m_GameObjects.insert(it, obj);
            return;
        }
    }
    curWorld->m_GameObjects.push_back(obj); 
}

