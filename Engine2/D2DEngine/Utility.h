#pragma once
#include <stdexcept>

class Utility
{
public:
	static int RandomBetween(int min, int max) 
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(min, max);
		return dis(gen);
	}

	static std::vector<int> RandomUniqueValuesFromVector(const std::vector<int>& elements, size_t count) //gpt코드
	{
		// 입력 검증
		if (count > elements.size())
		{
			throw std::invalid_argument("Count exceeds the number of unique values in the input vector.");
		}

		std::random_device rd;
		std::mt19937 gen(rd());

		// 복사된 벡터를 랜덤하게 섞음
		std::vector<int> shuffled_elements = elements;
		std::shuffle(shuffled_elements.begin(), shuffled_elements.end(), gen);

		// 처음 count 개의 요소를 선택
		std::vector<int> result(shuffled_elements.begin(), shuffled_elements.begin() + count);
		return result;
	}

	static float CalCul(std::string myType, std::string targetType, float damage)
	{
		

		if(targetType == "보스")
			return damage *= 0.75f;

		if (myType == "석궁형" && targetType == "속도형")
		{
			return damage *= 1.25;
		}
		else if (myType == "석궁형" && targetType == "방어형")
		{
			return damage *= 0.75;
		}
		else
		{
			return damage;
		}

		if (myType == "성수형" && targetType == "방어형")
		{
			return damage *= 1.25;
		}
		else if (myType == "성수형" && targetType == "속도형")
		{
			return damage *= 0.75;
		}
		else
		{
			return damage;
		}
	}

	template<typename T>
	static void removeElements(std::list<T*>& origin, const std::list<T*>& remove) { 
		for (auto it = remove.begin(); it != remove.end(); ++it) {
			origin.remove(*it);
		}
	}

	static std::wstring convertFromString(const std::string& str) { //이건그냥 옮겨닮는거라 영어는 잘변환되지만 한글은 안되네.. 
		std::wstring wstr;
		wstr.assign(str.begin(), str.end());
		return wstr;
	}

	static std::string convertFromWString(const std::wstring& wstr) { 
		std::string str;
		str.assign(wstr.begin(), wstr.end());
		return str;
	}

	static std::wstring StringToWString(const std::string& str)//gpt코드
	{
		// 입력 문자열의 길이 계산
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), NULL, 0);
		if (size_needed == 0)
		{
			throw std::runtime_error("Failed to determine the size needed for the conversion.");
		}

		// 변환을 위한 버퍼 할당
		std::wstring wstr(size_needed, 0);

		// 문자열 변환
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), &wstr[0], size_needed);

		return wstr;
	}

	// std::string을 std::wstring으로 변환하는 함수 (ANSI 인코딩 처리)
	static std::wstring StringToWStringA(const std::string& str) //gpt코드
	{
		// ANSI 코드 페이지로 변환할 문자열의 길이 계산
		int size_needed = MultiByteToWideChar(CP_ACP, 0, str.c_str(), static_cast<int>(str.size()), NULL, 0);
		if (size_needed == 0)
		{
			throw std::runtime_error("Failed to determine the size needed for the conversion.");
		}

		// 변환을 위한 버퍼 할당
		std::wstring wstr(size_needed, 0);

		// 문자열 변환
		int result = MultiByteToWideChar(CP_ACP, 0, str.c_str(), static_cast<int>(str.size()), &wstr[0], size_needed);
		if (result == 0)
		{
			throw std::runtime_error("Failed to convert string to wstring.");
		}

		return wstr;
	}
};

