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

GameObject* Factory::CreateImage(std::wstring filePath, MathHelper::Vector2F pos, MathHelper::Vector2F scale, std::vector<GameObject*>* Root) //크기값도 조절 많이할거같은데.. 
{
    Image* img = new Image(L"../Data/Image/" + filePath);
    img->transform->SetRelativeLocation(pos);
    img->transform->SetRelativeScale(scale);
    if (Root == nullptr)
        InsertWorld(img);
    else
        Root->push_back(img); //이런식으로 처리하는게 나을려나? 중복되는 부분을 최대한 줄여야함.. 
    return img;
}

GameObject* Factory::CreateMoveIcon(std::wstring filePath, MathHelper::Vector2F pos) //UI는 생성할때 위치랑 크기조정을할거같아서 만들었는데 굳이 여기서 다 처리하는게 맞나 싶네.. 
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


