#pragma once
#include "SingletonBase.h"
#include "Data.h"

using namespace std;
using namespace MathHelper;

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
class EnemyBase;
class TowerBase;

class Image;
class MoveIcon;
class Button;
class Arrow;

class Factory : public SingletonBase<Factory>  
{
	map<int,TowerData> towerData; 
	map<int,EnemyData> enemyData; //위험하게 코딩할빠에 안전하게 맵으로하면되지.. 
public:
	Factory();
	~Factory();
	World* curWorld;
	void GetData(std::wstring DataPath);
    template<typename T>
	T* CreateGameObject() //어 맞다 이거 남겨놨구나 그럼 월드한테서 전부뺏을수있는거지? 
	{
		bool bIsBase = is_base_of<GameObject, T>::value;
		assert(bIsBase == true);
		T* newObject = new T();
		InsertWorld(newObject);
		return newObject;
	}

	Image* CreateImage(wstring filePath, Vector2F pos = { 0,0 }, Vector2F scale = { 1,1 }, std::vector<GameObject*>* Root = nullptr);
	MoveIcon* CreateMoveIcon(wstring filePath, Vector2F pos = { 0,0 }); //이거는 그럴필요는 없을거같고.. 
	GameObject* CreateGameObjectFromId(int id);
	template<typename T>
	T* CreateEnemy(int id);

	Button* CreateButton(wstring filePath, function<void(void)> func, Vector2F pos = { 0,0 }, std::vector<GameObject*>* Root = nullptr); //버튼은.. 생성자의 매개변수를 함수랑 기타등등 생각해보자.. 
	
	void InsertWorld(GameObject* obj);

	TowerBase* CreateTower(int id);
	Arrow* CreateBullet(int id); //성수, 화살, 적들것도 다여기서 만들거임

};

template<typename T>
T* Factory::CreateEnemy(int id) //애네들은 특히 데이터가 필요하고..
{
	bool bIsBase = is_base_of<EnemyBase, T>::value;
	assert(bIsBase == true);
	T* newObject = new T(enemyData[id]); //생성자에 데이터를 추가하는 방식이면 되겠지? 일관되게 관리하면.. cpp는 줄어들지만.. 각각의 변화에 제한이 생길수밖에 없음.. 
	InsertWorld(newObject);
	return newObject;

}

