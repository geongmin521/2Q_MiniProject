#pragma once
#include "../D2DEngine/SingletonBase.h"
#include "../D2DEngine/Data.h"

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
class Factory : public SingletonBase<Factory> //이친구 생각해보니 굳이 싱글톤으로 안해도되겠는데?
	//알고있어야하는애들이 각 월드랑, 오브젝트풀 3개인데.. 근데 또 각각의 인스턴스를 만들필요도없긴함.. 엄.. 
	//아니면 오브젝트풀은 싱글톤일거고.. 팩토리를 들고있을거니까 상관없을지도? 
{
	vector<TowerData> towerData; 
	vector<EnemyData> enemyData;
	vector<WaveData> waveData;

public:
	World* curWorld;
	void GetData();
    template<typename T>
	T* CreateGameObject() //매개변수가 없는경우에는 여기서 처리하면될거고.. 
	{
		bool bIsBase = is_base_of<GameObject, T>::value;
		assert(bIsBase == true);
		T* newObject = new T();
		InsertWorld(newObject);
		return newObject;
	}//아니면 특수화를 시킬까? 그래도 매개변수는 못받으니까 패스.. 

	//루트이면.. 월드에 직접넣고 아닌경우에는 부모UI가 따로 있다는거니까 거기에 넣어주기..
	//아 근데 이렇게 약속하면 편하긴한데.. 이것도 잘못사용할 원인이 너무 많을거같아.. 
	//시스템적으로 프로그래머의 실수를 방지할수있어야하는데.. 

	//디폴트 매개변수도 너무 많아지면 문제가있음.. 마지막 값을 채우기 위해 원치않는 값들을 채워야해.. 
	//이건 어쩔수없나? 하.. 
	//매개변수가 너무 많은데 깔끔하게 처리하는방법없나? 가변인자로는 처리가능한가? 
	GameObject* CreateImage(wstring filePath, Vector2F pos = { 0,0 }, Vector2F scale = { 1,1 }, std::vector<GameObject*>* Root = nullptr);
	GameObject* CreateMoveIcon(wstring filePath, Vector2F pos = { 0,0 }); //이거는 그럴필요는 없을거같고.. 
	GameObject* CreateEnemy(int id); 
	GameObject* CreateTower(int id); 
	GameObject* CreateButton(wstring filePath, function<void(void)> func, Vector2F pos = { 0,0 }, std::vector<GameObject*>* Root = nullptr); //버튼은.. 생성자의 매개변수를 함수랑 기타등등 생각해보자.. 
	
	//단순 팩토리로 만들어서.. 각각의 구체클래스에 대해서 다양한 생성방식을 둬야겠다.. 
	//멤버변수로 들고있다면.. 매개변수가 필요없지않을까? 그렇다면 추상클래스로 묶인 서브 팩토리를 자유롭게 만들수있을지도? 
	void InsertWorld(GameObject* obj);

};

