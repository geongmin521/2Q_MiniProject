#pragma once
#include "SingletonBase.h"
#include "Data.h"


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

class World;
class GameObject;
class Factory : public SingletonBase<Factory> 
{
	std::vector<TowerData> towerData; 
	std::vector<EnemyData> enemyData;
	std::vector<WaveData> waveData;

public:
	World* curWorld;
	void GetData();
    template<typename T>
	T* CreateGameObject() //매개변수가 없는경우에는 여기서 처리하면될거고.. 
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);
		T* newObject = new T();
		InsertWorld(newObject);
		return newObject;
	}//아니면 특수화를 시킬까? 그래도 매개변수는 못받으니까 패스.. 

	void CreateImage(std::wstring filePath); //매개변수 필요한애들을따로만들기? 
	void CreateEnemy(int id); 
	void CreateTower(int id); 
	void CreateButton(std::wstring filePath); //버튼은.. 생성자의 매개변수를 함수랑 기타등등 생각해보자.. 
	
	//단순 팩토리로 만들어서.. 각각의 구체클래스에 대해서 다양한 생성방식을 둬야겠다.. 
	//멤버변수로 들고있다면.. 매개변수가 필요없지않을까? 그렇다면 추상클래스로 묶인 서브 팩토리를 자유롭게 만들수있을지도? 
	void InsertWorld(GameObject* obj);

};

