#include "../D2DEngine/pch.h"
#include "Factory.h"

#include "../D2DEngine/DataManager.h"
#include "../D2DEngine//Transform.h"
#include "../D2DEngine/World.h"

#include "Image.h"
#include "EnemyBase.h"
#include "TowerBase.h"
#include "ArrowTower.h"
#include "Button.h"
#include "MoveIcon.h"


Factory::Factory()
{
    GetData(L"TowerData"); //생성되는시점에 데이터들고있기
    GetData(L"EnemyData");
}

Factory::~Factory()
{
}

void Factory::GetData(std::wstring DataPath)//variant 처리한게 잘한걸까? 일관성으로 코드를 줄인거같기도하고 아닌거같기도하고.. 
{ 
    std::variant<std::vector<EnemyData>, std::vector<TowerData>, std::vector<WaveData>> data =
        DataManager::GetInstance().get()->CSVReader(DataPath);
    
    if (std::holds_alternative<std::vector<EnemyData>>(data)) {
        for(auto var : std::get<std::vector<EnemyData>>(data))        
            enemyData[var.id] = var;        
    }
    else if (std::holds_alternative<std::vector<TowerData>>(data)) {
        for (auto var : std::get<std::vector<TowerData>>(data))
            towerData[var.id] = var;     //아이디를 키값으로 맵에 넣어주기   
    }
}

Image* Factory::CreateImage(std::wstring filePath, MathHelper::Vector2F pos, MathHelper::Vector2F scale, std::vector<GameObject*>* Root) //크기값도 조절 많이할거같은데.. 
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

MoveIcon* Factory::CreateMoveIcon(std::wstring filePath, MathHelper::Vector2F pos) //UI는 생성할때 위치랑 크기조정을할거같아서 만들었는데 굳이 여기서 다 처리하는게 맞나 싶네.. 
{
    MoveIcon* icon = new MoveIcon(L"../Data/Image/"+filePath);
    icon->transform->SetRelativeLocation(pos); 
    InsertWorld(icon);
    return icon;
}



Button* Factory::CreateButton(std::wstring filePath , std::function<void(void)> func, MathHelper::Vector2F pos, std::vector<GameObject*>* Root)
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


