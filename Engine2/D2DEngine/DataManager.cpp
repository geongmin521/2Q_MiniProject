#include "pch.h"
#include "DataManager.h"
#include <locale>
#include <codecvt>
DataManager::DataManager()
{
	CSVReader(L"EnemyData");
	CSVReader(L"TowerData");
	CSVReader(L"WaveData");
	CSVReader(L"ArtifactData");
}

DataManager::~DataManager()
{
}

template <typename T>
T convertFromString(const std::wstring& str);//csv의 모든 형식은 int, float, wstring 이 3개로 구분됨

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
std::string convertFromString<std::string>(const std::wstring& wstr) { //어뭐야.. wstring에서 string형변환하니까.. 한글이 들어오네? 
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

//데이터 매니저가 전부 들고있는게 좋아? 아니면.. 필요한 각자가 들고있는게 맞긴하지? 
//팩토리가 처음에 저것들을 요청하고.. 오케이.. 
//반환값이 3개중에 하나가 가능한거지? 
std::variant<std::vector<EnemyData>, std::vector<TowerData>, std::vector<WaveData>, std::vector<ArtifactData>> DataManager::CSVReader(std::wstring fileName)
{
	std::wifstream file = FileOften(fileName); //얘가 다들고있을거면 variation은 왜함? 이게 싱글톤이면.. 쌉가능이지
    if (fileName == L"EnemyData") 
        return EnemyDataRead(file);
    else if (fileName == L"TowerData") 
        return TowerDataRead(file);
    else if (fileName == L"WaveData") 
        return WaveDataRead(file);
	else if (fileName == L"ArtifactData")
		return ArtifactDataRead(file);
    else {
        assert(false && "Unsupported type in CSVReader");
        return {}; // Unreachable code; returns an empty variant to suppress compiler warnings
    }
}

std::vector<EnemyData> DataManager::EnemyDataRead(std::wifstream& file)
{
	std::vector<EnemyData> result;
	std::wstring line;
	while (std::getline(file, line)) {
	
		if (!line.empty()) {
			EnemyData data;
			std::wstringstream wss(line);   // 한줄을 읽어서 wstringstream에 저장
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
				parseToken(wss, data.speed);
				parseToken(wss, data.ability);
			}
			result.push_back(data);
		}
	}
	return result;

}

std::vector<TowerData> DataManager::TowerDataRead(std::wifstream& file)
{
	std::vector<TowerData> result;
	std::wstring line;
	while (std::getline(file, line)) {

		if (!line.empty()) {
			TowerData data;
			std::wstringstream wss(line);   // 한줄을 읽어서 wstringstream에 저장
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
				parseToken(wss, data.ability);
			}
			result.push_back(data);
		}
	}
	return result;
}

std::vector<WaveData> DataManager::WaveDataRead(std::wifstream& file)
{
	std::vector<WaveData> result;
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
				parseTokens(wss, data.enemyId); //s에 주의하기.. 이거는 여러개가져오는거다
				parseTokens(wss, data.spawnTime);
				parseTokens(wss, data.enemyCount);
			}
			result.push_back(data);
		}
	}
	return result;
}

std::vector<ArtifactData> DataManager::ArtifactDataRead(std::wifstream& file)
{
	std::vector<ArtifactData> result;
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
			result.push_back(data);
		}
	}
	return result;
}
