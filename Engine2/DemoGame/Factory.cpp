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
    GetData(L"TowerData"); //�����Ǵ½����� �����͵���ֱ�
    GetData(L"EnemyData");
}

Factory::~Factory()
{
}

void Factory::GetData(std::wstring DataPath)//variant ó���Ѱ� ���Ѱɱ�? �ϰ������� �ڵ带 ���ΰŰ��⵵�ϰ� �ƴѰŰ��⵵�ϰ�.. 
{ 
    std::variant<std::vector<EnemyData>, std::vector<TowerData>, std::vector<WaveData>> data =
        DataManager::GetInstance().get()->CSVReader(DataPath);
    
    if (std::holds_alternative<std::vector<EnemyData>>(data)) {
        for(auto var : std::get<std::vector<EnemyData>>(data))        
            enemyData[var.id] = var;        
    }
    else if (std::holds_alternative<std::vector<TowerData>>(data)) {
        for (auto var : std::get<std::vector<TowerData>>(data))
            towerData[var.id] = var;     //���̵� Ű������ �ʿ� �־��ֱ�   
    }
}

Image* Factory::CreateImage(std::wstring filePath, MathHelper::Vector2F pos, MathHelper::Vector2F scale, std::vector<GameObject*>* Root) //ũ�Ⱚ�� ���� �����ҰŰ�����.. 
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

MoveIcon* Factory::CreateMoveIcon(std::wstring filePath, MathHelper::Vector2F pos) //UI�� �����Ҷ� ��ġ�� ũ���������ҰŰ��Ƽ� ������µ� ���� ���⼭ �� ó���ϴ°� �³� �ͳ�.. 
{
    MoveIcon* icon = new MoveIcon(L"../Data/Image/"+filePath);
    icon->transform->SetRelativeLocation(pos); 
    InsertWorld(icon);
    return icon;
}

//� UI�� ��ġ�� �̵� �������� �޶������ְ�.. 
//��ġ�� ũ�������� �����ڿ��� ��������.. �ƴϸ� ���丮�� �̾���̸鼭 �� �Ҽ��ֳ�? ���� Ȯ�强�� ���ʿ��ҰŰ�����.. 

//���丮�� ��� �ش޶�� ��û�Ұǵ�.. 
//���Ÿ� �̹����� ���鶧 �����ڿ��� ó���ϴ°Ը³�? 
//�̹��������������ְ� ���������ְ�..
//�ؽ�Ʈ�� ���������ְ� ���������ְ�? 
//��ư�����������ְ� ���������ְ�? �������ڸ� Ȱ���غ����������� �ؾ������� �߸𸣰��ݾ�... 
//���� �� ������ ���ۿ� �ӽ÷� ��Ƴְ� �������� ����Ǵ�? �׷����غ���;��µ�.. 

//�ƴϸ� �Լ���ü�� Ȱ���ϴ°� �? �̰͵� �� ���� ����� �ɼ������Ű�����? 
//�Ϻ����� �Լ��� ��ü�� ����ؼ�.. �� �Ź��� ���̵���̱��ѵ�.. �߸𸣰ڳ�.. �ϴ� �н�? 

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


