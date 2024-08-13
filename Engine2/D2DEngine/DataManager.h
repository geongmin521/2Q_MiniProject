#pragma once
#include "SingletonBase.h"
#include "Data.h"

class DataManager : public SingletonBase<DataManager> //각 데이터를 읽어와서 요청한애한테 담는 부분 만들었고.. 
{
private:
    void EnemyDataRead();
    void TowerDataRead();
    void WaveDataRead(); 
    void ArtifactDataRead();
    std::map<int, TowerData> towerData;
    std::map<int, EnemyData> enemyData;
    std::map<int, WaveData> waveData;
    std::map<int, ArtifactData> artifactData;
public:
    TowerData& getTowerData(int id) {return towerData[id];}
    EnemyData& getEnemyData(int id) {return enemyData[id];}
    WaveData& getWaveData(int id) { return waveData[id]; };
    void ChoseWave();
    ArtifactData& getArtifactData(int id) {return artifactData[id];}   
    DataManager();
    ~DataManager();
    std::wifstream FileOften(std::wstring fileName);
};