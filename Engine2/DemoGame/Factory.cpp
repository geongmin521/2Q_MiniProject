#include "pch.h"
#include "Factory.h"

#include "DataManager.h"
#include "Transform.h"
#include "World.h"
#include "SceneManager.h"
#include "D2DFont.h"
#include "Bitmap.h"

//Fluent Interface 패턴 설명 매서드에서 본인을 반환하여 체이닝을 통해 원하는값을 설정할수있도록하는 패턴인데
//이걸통해 매개변수에 굳이 추가하지않더라도.. 다양한 세팅을 공장에서 마친다음에 반환할수있지만
// 생성할때의 길이는 좀더 길어지는단점있지만.. 확장성은 절대강자이고 디폴트 매개변수도 쓰지않아도됨
// 즉좋음.. 
//심지어 안전하게 유지하는것도 가능할듯? 

//내가 원하는 팩토리이 이긴했는데.. 막상 쭉 늘여놓으니까 가독성이 별로네.. 이건 어쩔수 없는건가? 
Factory::Factory() //흠 상태유지가 필요없으니까 굳이 싱글톤으로? 물론 생성삭제가 일어나서 성능이좀 떨어지겠지만.. 초기과정에서만 많이일어나니까 성능이슈도 거의없을듯? 
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

Factory& Factory::setScale(Vector2F scale) {
    object->transform->SetRelativeScale(scale);
    return *this;
}

Factory& Factory::setParent(Transform* parent)
{
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
    object->isActive = active;
    return *this;
}

Factory& Factory::setRenderOrder(int order)
{
    object->renderOrder = order;
    return *this;
}

Factory& Factory::AddText(std::wstring text, int size)
{
    D2DFont* Text = new D2DFont(text); 
    object->AddComponent(Text);
    Bitmap* bitmap = object->GetComponent<Bitmap>();
    if(bitmap != nullptr)
        Text->SetBoxSize(bitmap->GetSize()); //아 뭐만해도 다 파괴되서 이전의 적용사항이 사라지구나.. 하.. 뭐 이런 텍스트 클래스가 다있냐... 
    Text->SetSize(size, { 0,(unsigned int)text.size() });
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

