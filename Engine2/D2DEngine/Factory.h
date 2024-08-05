#pragma once
#include "DataManager.h"
//#include "SingletonBase.h"


struct VariantVisitor {
    std::vector<TowerData>& operator()( std::vector<TowerData>& towerData) {
        return towerData;
    }

    std::vector<EnemyData>& operator()(std::vector<EnemyData>& enemyData) {
        return enemyData;
    }

    std::vector<WaveData>& operator()(std::vector<WaveData>& waves) {
        return waves;
    }
};

class Factory : public SingletonBase<Factory> 
{
	std::vector<TowerData> towerData; //포인터로 처리하던가.. 아무튼 값복사가 일어나지않게.. 참조로 처리하기.. 
	std::vector<EnemyData> enemyData;
	std::vector<WaveData> waveData;
	void GetData() { 

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

    //template<typename T>
	//T* CreateGameObject() //월드에 있는 함수 그대로 가져옴.. 
	//{
	//	bool bIsBase = std::is_base_of<GameObject, T>::value;
	//	assert(bIsBase == true);
	//	T* newObject = new T();
	//	newObject->SetOwner(this); //이건 어떻게되는거지 도대체.. 
	//	
	//	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	//	{
	//		if ((*it)->renderOrder > newObject->renderOrder)
	//		{
	//			m_GameObjects.insert(it, newObject); 
	//			return newObject; 
	//		}			
	//	}
	//	
	//	m_GameObjects.push_back(newObject); //나머지 상황에 대해서는 뒤에 넣기
	//
	//	return newObject;
	//}
    //지금 월드에서 처리하는 인스턴스의 생성을 얘한테 위임하고싶음
    //일단 함수만 가져와서 만들어놓고 사용은 하지말아보자.
};

