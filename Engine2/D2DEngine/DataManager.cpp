#include "pch.h"
#include "DataManager.h"
#include "GameManager.h"
#include "Utility.h"
#include <locale>
#include <codecvt>

DataManager::DataManager()
{
	EnemyDataRead();
	TowerDataRead();
	WaveDataRead();
	//ArtifactDataRead(); //아직 csv 없음
}

DataManager::~DataManager()
{

}

template <typename T>
T convertFromString(const std::wstring& str);

// 특수화: int형 변환
template <>
int convertFromString<int>(const std::wstring& str) {
	return _wtoi(str.c_str());
}

// 특수화: float형 변환
template <>
float convertFromString<float>(const std::wstring& str) {
	return static_cast<float>(_wtof(str.c_str()));
}

// 특수화: string //와이드 스트링을 일반 스트링으로변경
template <>
std::string convertFromString<std::string>(const std::wstring& wstr) { 
	std::string str;
	str.assign(wstr.begin(), wstr.end());
	return str;
}

// 파싱 함수
template <typename T>
void parseToken(std::wstringstream& wss, T& var) {
	std::wstring token;
	std::getline(wss, token, L',');
	var = convertFromString<T>(token);
}

// 파싱 함수
template <typename T>
void parseTokens(std::wstringstream& wss, std::vector<T>& var) { //토큰내에 여러개 가져오기.. 
	std::wstring token;
	std::getline(wss, token, L',');

	std::wstringstream tokenStream(token);
	std::wstring subToken;
	while (std::getline(tokenStream, subToken, L'_')) {
		var.push_back(convertFromString<T>(subToken));
	}
}

std::wifstream DataManager::FileOften(std::wstring fileName)
{
	std::wifstream file(L"..\\Data\\CSV\\"+ fileName + L".csv"); //읽기
	if (!file.is_open()) {
		assert(false && "파일이 존재하지 않습니다.");
	}
	std::wstring line;			
	std::getline(file, line); //첫 두줄은 날리기
	std::getline(file, line);
	return file;
}

void DataManager::EnemyDataRead()
{
	std::wifstream file = FileOften(L"EnemyData");
	std::wstring line;
	while (std::getline(file, line)) {
	
		if (!line.empty()) {
			EnemyData data;
			std::wstringstream wss(line);  
			std::wstring token;
			{
				parseToken(wss, data.id);
				parseToken(wss, data.name);
				parseToken(wss, data.level);
				parseToken(wss, data.Type);
				parseToken(wss, data.ATK);
				parseToken(wss, data.attackRange);
				parseToken(wss, data.detectRange);
				parseToken(wss, data.HP);
				parseToken(wss, data.attackSpeed);
				parseToken(wss, data.speed);
				parseToken(wss, data.ability);
			}
			enemyData[data.id] = data;
		}
	}


}

void DataManager::TowerDataRead()
{
	std::wifstream file = FileOften(L"TowerData");
	std::wstring line;
	while (std::getline(file, line)) {

		if (!line.empty()) {
			TowerData data;
			std::wstringstream wss(line);  
			std::wstring token;
			{
				parseToken(wss, data.id);
				parseToken(wss, data.name);
				parseToken(wss, data.level);
				parseToken(wss, data.Type);
				parseToken(wss, data.ATK);
				parseToken(wss, data.attackRange);
				parseToken(wss, data.HP);
				parseToken(wss, data.attackSpeed);
				parseToken(wss, data.attackArea);
				parseToken(wss, data.knockBack);
				parseToken(wss, data.ability);
			}
			towerData[data.id] = data;
		}
	}
}

void DataManager::WaveDataRead()
{
	std::wifstream file = FileOften(L"WaveData");
	std::wstring line;
	while (std::getline(file, line)) {

		if (!line.empty()) {
			WaveData data;
			std::wstringstream wss(line);   // 한줄을 읽어서 wstringstream에 저장
			std::wstring token;
			{
				parseToken(wss, data.id);
				parseToken(wss, data.level);
				parseToken(wss, data.levelPower);
				parseTokens(wss, data.enemyId); 
				parseTokens(wss, data.spawnTime);
				parseTokens(wss, data.enemyCount);
			}
			waveData[data.id] = data;
		}
	}
}

void DataManager::ArtifactDataRead()
{
	std::wifstream file = FileOften(L"ArtifactData");
	std::wstring line;
	while (std::getline(file, line)) {

		if (!line.empty()) {
			ArtifactData data;
			std::wstringstream wss(line);   // 한줄을 읽어서 wstringstream에 저장
			std::wstring token;
			{
				parseToken(wss, data.id);
				parseToken(wss, data.level);
				parseToken(wss, data.towerDamage);
				parseToken(wss, data.enemyDamage);
				parseToken(wss, data.count);
				parseToken(wss, data.name);
				parseToken(wss, data.ability);
			}
			artifactData[data.id] = data;
		}
	}
}

void DataManager::ChoseWave() //같은 레벨중에 택1
{
	std::vector<WaveData> result;

	for (const auto& entry : waveData) {
		const WaveData& data = entry.second;
		if (data.level == gameManager->WaveLevel) {
			result.push_back(data);
		}
	}

	if (result.empty()) {
		throw std::out_of_range("No WaveData with the specified level.");
	}

	int id = Utility::RandomBetween(0, result.size() - 1);
	gameManager->curWaveId = result[id].id;
}