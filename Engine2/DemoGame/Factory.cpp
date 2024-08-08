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

//어떤 UI든 위치와 이동 조정등이 달라질수있고.. 
//위치랑 크기조정은 생성자에서 하지말자.. 아니면 팩토리에 이어붙이면서 좀 할수있나? 좀더 확장성이 더필요할거같은데.. 

//팩토리에 어떻게 해달라고 요청할건데.. 
//저거를 이미지를 만들때 생성자에서 처리하는게맞나? 
//이미지가있을수도있고 없을수도있고..
//텍스트가 있을수도있고 없을수도있고? 
//버튼이있을수도있고 없을수도있고? 가변인자를 활용해보고싶은데어떻게 해야할지를 잘모르겠잖아... 
//지금 든 생각은 버퍼에 임시로 담아넣고 넣을때만 적용되는? 그런걸해보고싶었는데.. 

//아니면 함수객체를 활용하는건 어때? 이것도 꽤 좋은 방법이 될수있을거같은데? 
//꽤복잡한 함수를 객체를 사용해서.. 꽤 신박한 아이디어이긴한데.. 잘모르겠네.. 일단 패스? 

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


