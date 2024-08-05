#include "pch.h"
#include "Factory.h"
#include "DataManager.h"
#include "World.h"

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

void Factory::InsertWorld(GameObject* obj)
{
    //여기에 set으로 world 넣어주는거 일단지움
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


