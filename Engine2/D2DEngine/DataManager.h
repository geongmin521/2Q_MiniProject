#pragma once
#include "SingletonBase.h"
#include "Data.h"


class DataManager : public SingletonBase<DataManager> //각 데이터를 읽어와서 요청한애한테 담는 부분 만들었고.. 
{
private:
    std::vector<EnemyData> EnemyDataRead();
    std::vector<TowerData> TowerDataRead();
    std::vector<WaveData> WaveDataRead();
public:
    DataManager();
    ~DataManager();

    // std::variant를 사용하여 여러 타입을 하나의 반환 타입으로 처리
    std::variant<std::vector<EnemyData>, std::vector<TowerData>, std::vector<WaveData>> CSVReader(const std::type_info& typeInfo);
    //필요한객체가 이걸 그냥 호출하기만 하면됨
};