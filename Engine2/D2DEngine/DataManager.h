#pragma once
#include "SingletonBase.h"
#include "Data.h"

#define dataManager DataManager::GetInstance().get()

class DataManager : public SingletonBase<DataManager> 
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