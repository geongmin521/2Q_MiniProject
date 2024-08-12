#include "pch.h"
#include "Factory.h"

#include "DataManager.h"
#include "Transform.h"
#include "World.h"
#include "SceneManager.h"
#include "D2DFont.h"
#include "Bitmap.h"

//Fluent Interface ���� ���� �ż��忡�� ������ ��ȯ�Ͽ� ü�̴��� ���� ���ϴ°��� �����Ҽ��ֵ����ϴ� �����ε�
//�̰����� �Ű������� ���� �߰������ʴ���.. �پ��� ������ ���忡�� ��ģ������ ��ȯ�Ҽ�������
// �����Ҷ��� ���̴� ���� ������´���������.. Ȯ�强�� ���밭���̰� ����Ʈ �Ű������� �����ʾƵ���
// ������.. 
//������ �����ϰ� �����ϴ°͵� �����ҵ�? 

//���� ���ϴ� ���丮�� �̱��ߴµ�.. ���� �� �ÿ������ϱ� �������� ���γ�.. �̰� ��¿�� ���°ǰ�? 
Factory::Factory() //�� ���������� �ʿ�����ϱ� ���� �̱�������? ���� ���������� �Ͼ�� �������� ������������.. �ʱ���������� �����Ͼ�ϱ� �����̽��� ���Ǿ�����? 
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
        Text->SetBoxSize(bitmap->GetSize()); //�� �����ص� �� �ı��Ǽ� ������ ��������� ���������.. ��.. �� �̷� �ؽ�Ʈ Ŭ������ ���ֳ�... 
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

