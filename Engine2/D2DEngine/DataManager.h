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
    std::vector<int> normalArtifactID; //아이디만 따로 저장해놓자..
    std::vector<int> SpecialArtifactID;
public:
    TowerData& getTowerData(int id) {return towerData[id];}
    EnemyData& getEnemyData(int id) {return enemyData[id];}
    WaveData& getWaveData(int id) { return waveData[id]; };
    void ChoseWave();
    ArtifactData& getArtifactData(int id) {return artifactData[id];}   
    std::vector<int> getNormalArtifactID() {return normalArtifactID;}
    std::vector<int> getSpecialArtifactID() {return SpecialArtifactID;}
    DataManager();
    ~DataManager();	
    virtual void reset() override;
    std::wifstream FileOften(std::wstring fileName);
};