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
T convertFromString(const std::wstring& str);//csv�� ��� ������ int, float, wstring �� 3���� ���е�

// Ư��ȭ: int�� ��ȯ
template <>
int convertFromString<int>(const std::wstring& str) {
	return _wtoi(str.c_str());
}

// Ư��ȭ: float�� ��ȯ
template <>
float convertFromString<float>(const std::wstring& str) {
	return static_cast<float>(_wtof(str.c_str()));
}

// Ư��ȭ: string //���̵� ��Ʈ���� �Ϲ� ��Ʈ�����κ���
template <>
std::string convertFromString<std::string>(const std::wstring& wstr) { //���.. wstring���� string����ȯ�ϴϱ�.. �ѱ��� ������? 
	std::string str;
	str.assign(wstr.begin(), wstr.end());
	return str;
}

// �Ľ� �Լ�
template <typename T>
void parseToken(std::wstringstream& wss, T& var) {
	std::wstring token;
	std::getline(wss, token, L',');
	var = convertFromString<T>(token);
}

// �Ľ� �Լ�
template <typename T>
void parseTokens(std::wstringstream& wss, std::vector<T>& var) { //��ū���� ������ ��������.. 
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
	std::wifstream file(L"..\\Data\\CSV\\"+ fileName + L".csv"); //�б�
	if (!file.is_open()) {
		assert(false && "������ �������� �ʽ��ϴ�.");
	}
	std::wstring line;			
	std::getline(file, line); //ù ������ ������
	std::getline(file, line);
	return file;
}

//������ �Ŵ����� ���� ����ִ°� ����? �ƴϸ�.. �ʿ��� ���ڰ� ����ִ°� �±�����? 
//���丮�� ó���� ���͵��� ��û�ϰ�.. ������.. 
//��ȯ���� 3���߿� �ϳ��� �����Ѱ���? 
std::variant<std::vector<EnemyData>, std::vector<TowerData>, std::vector<WaveData>, std::vector<ArtifactData>> DataManager::CSVReader(std::wstring fileName)
{
	std::wifstream file = FileOften(fileName); //�갡 �ٵ�������Ÿ� variation�� ����? �̰� �̱����̸�.. �԰�������
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
			std::wstringstream wss(line);   // ������ �о wstringstream�� ����
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
			std::wstringstream wss(line);   // ������ �о wstringstream�� ����
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
			std::wstringstream wss(line);   // ������ �о wstringstream�� ����
			std::wstring token;
			{
				parseToken(wss, data.id);
				parseToken(wss, data.level);
				parseToken(wss, data.levelPower);
				parseTokens(wss, data.enemyId); //s�� �����ϱ�.. �̰Ŵ� �������������°Ŵ�
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
			std::wstringstream wss(line);   // ������ �о wstringstream�� ����
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
