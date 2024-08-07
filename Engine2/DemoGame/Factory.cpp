#include "../D2DEngine/pch.h"
#include "Factory.h"

#include "../D2DEngine/DataManager.h"
#include "../D2DEngine//Transform.h"
#include "../D2DEngine/World.h"

#include "Image.h"
#include "EnemyBase.h"
#include "TowerBase.h"
#include "Button.h"
#include "MoveIcon.h"


void Factory::GetData()
{ 
    std::variant<std::vector<EnemyData>, std::vector<TowerData>, std::vector<WaveData>> data =
        DataManager::GetInstance().get()->CSVReader(typeid(TowerData));

    if (std::holds_alternative<std::vector<EnemyData>>(data)) {
        enemyData = std::get<std::vector<EnemyData>>(data);
    }
    else if (std::holds_alternative<std::vector<TowerData>>(data)) {
        towerData = std::get<std::vector<TowerData>>(data);
    }
    else if (std::holds_alternative<std::vector<WaveData>>(data)) {
        waveData = std::get<std::vector<WaveData>>(data);
    }
}

GameObject* Factory::CreateImage(std::wstring filePath, MathHelper::Vector2F pos, MathHelper::Vector2F scale, std::vector<GameObject*>* Root) //ũ�Ⱚ�� ���� �����ҰŰ�����.. 
{
    Image* img = new Image(L"../Data/Image/" + filePath);
    img->transform->SetRelativeLocation(pos);
    img->transform->SetRelativeScale(scale);
    if (Root == nullptr)
        InsertWorld(img);
    else
        Root->push_back(img); //�̷������� ó���ϴ°� ��������? �ߺ��Ǵ� �κ��� �ִ��� �ٿ�����.. 
    return img;
}

GameObject* Factory::CreateMoveIcon(std::wstring filePath, MathHelper::Vector2F pos) //UI�� �����Ҷ� ��ġ�� ũ���������ҰŰ��Ƽ� ������µ� ���� ���⼭ �� ó���ϴ°� �³� �ͳ�.. 
{
    MoveIcon* icon = new MoveIcon(L"../Data/Image/"+filePath);
    icon->transform->SetRelativeLocation(pos); 
    InsertWorld(icon);
    return icon;
}

GameObject* Factory::CreateEnemy(int id)
{
    //InsertWorld(btn);
    //return new EnemyBase(id); 
    return nullptr;
}

GameObject* Factory::CreateTower(int id)
{
    //InsertWorld(btn);
    //return new TowerBase(id);
    return nullptr;
}

GameObject* Factory::CreateButton(std::wstring filePath , std::function<void(void)> func, MathHelper::Vector2F pos, std::vector<GameObject*>* Root)
{
    Button* btn = new Button(L"../Data/Image/" + filePath);
    btn->AddListener(func);
    btn->transform->SetRelativeLocation(pos); 
    if (Root == nullptr)
        InsertWorld(btn);
    else
        Root->push_back(btn);
    return btn;                               
}

void Factory::InsertWorld(GameObject* obj)
{
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


