#include "pch.h"
#include "DataManager.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

std::variant<std::vector<EnemyData>, std::vector<TowerData>, std::vector<WaveData>> DataManager::CSVReader(const std::type_info& typeInfo)
{
    //이걸 실행하기 전에.. 파일을 여는과정도 겹치기 때문에.. 이걸어떻게 처리하고 가고싶은데..
    // 그리고 csv읽을때.. 시트가 다른건 어떻게 처리되는지 궁금함.. 애니메이션도 여기서 처리할수있게 만들기.. 

    if (typeInfo == typeid(EnemyData)) {
        return EnemyDataRead();
    }
    else if (typeInfo == typeid(TowerData)) {
        return TowerDataRead();
    }
    else if (typeInfo == typeid(WaveData)) {
        return WaveDataRead();
    }
    else {
        assert(false && "Unsupported type in CSVReader");
        return {}; // Unreachable code; returns an empty variant to suppress compiler warnings
    }
}

std::vector<EnemyData> DataManager::EnemyDataRead()
{
	std::wifstream file(L"..\\Data\\EnemyData.csv"); //읽기
	if (!file.is_open()) {
		assert(false && "파일이 존재하지 않습니다.");
	}
	std::wstring line;			// 한줄의 문자열	
	int DataCount = 0;			
	{
		std::getline(file, line);		// 첫번째 줄 읽기
		std::wstringstream wss(line);
		wss >> DataCount;
	}//윗부분은 모두 중복이라 제거할 방법 생각하기
	std::vector<EnemyData> result;
	for (int j = 0; j < DataCount; j++)
	{
		EnemyData data;

		getline(file, line);			// 한줄 읽기
		std::wstringstream wss(line);   // 한줄을 읽어서 wstringstream에 저장
		std::wstring token;
		{
			getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리
			//col->m_Center.x = (float)_wtoi(token.c_str()); //데이터의 순서에 맞게 순서대로 넣어주면됨
			getline(wss, token, L',');
			//col->m_Center.y = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			//col->m_Extent.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			//col->m_Extent.y = (float)_wtoi(token.c_str());
		}
		result.push_back(data);  //값을 그냥 가지고 있는거보단.. 동적할당으로 가지고있는게 맞겠지? 
	}
	return result;

}

std::vector<TowerData> DataManager::TowerDataRead()
{
	return std::vector<TowerData>();
}

std::vector<WaveData> DataManager::WaveDataRead()
{
	return std::vector<WaveData>();
}
