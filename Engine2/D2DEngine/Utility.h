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

	static std::vector<int> RandomUniqueValuesFromVector(const std::vector<int>& elements, size_t count) //gpt�ڵ�
	{
		// �Է� ����
		if (count > elements.size())
		{
			throw std::invalid_argument("Count exceeds the number of unique values in the input vector.");
		}

		std::random_device rd;
		std::mt19937 gen(rd());

		// ����� ���͸� �����ϰ� ����
		std::vector<int> shuffled_elements = elements;
		std::shuffle(shuffled_elements.begin(), shuffled_elements.end(), gen);

		// ó�� count ���� ��Ҹ� ����
		std::vector<int> result(shuffled_elements.begin(), shuffled_elements.begin() + count);
		return result;
	}

	static float CalCul(std::string myType, std::string targetType, float damage)
	{
		

		if(targetType == "����")
			return damage *= 0.75f;

		if (myType == "������" && targetType == "�ӵ���")
		{
			return damage *= 1.25;
		}
		else if (myType == "������" && targetType == "�����")
		{
			return damage *= 0.75;
		}
		else
		{
			return damage;
		}

		if (myType == "������" && targetType == "�����")
		{
			return damage *= 1.25;
		}
		else if (myType == "������" && targetType == "�ӵ���")
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

	static std::wstring convertFromString(const std::string& str) { //�̰Ǳ׳� �Űܴ�°Ŷ� ����� �ߺ�ȯ������ �ѱ��� �ȵǳ�.. 
		std::wstring wstr;
		wstr.assign(str.begin(), str.end());
		return wstr;
	}

	static std::string convertFromWString(const std::wstring& wstr) { 
		std::string str;
		str.assign(wstr.begin(), wstr.end());
		return str;
	}

	static std::wstring StringToWString(const std::string& str)//gpt�ڵ�
	{
		// �Է� ���ڿ��� ���� ���
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), NULL, 0);
		if (size_needed == 0)
		{
			throw std::runtime_error("Failed to determine the size needed for the conversion.");
		}

		// ��ȯ�� ���� ���� �Ҵ�
		std::wstring wstr(size_needed, 0);

		// ���ڿ� ��ȯ
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), &wstr[0], size_needed);

		return wstr;
	}

	// std::string�� std::wstring���� ��ȯ�ϴ� �Լ� (ANSI ���ڵ� ó��)
	static std::wstring StringToWStringA(const std::string& str) //gpt�ڵ�
	{
		// ANSI �ڵ� �������� ��ȯ�� ���ڿ��� ���� ���
		int size_needed = MultiByteToWideChar(CP_ACP, 0, str.c_str(), static_cast<int>(str.size()), NULL, 0);
		if (size_needed == 0)
		{
			throw std::runtime_error("Failed to determine the size needed for the conversion.");
		}

		// ��ȯ�� ���� ���� �Ҵ�
		std::wstring wstr(size_needed, 0);

		// ���ڿ� ��ȯ
		int result = MultiByteToWideChar(CP_ACP, 0, str.c_str(), static_cast<int>(str.size()), &wstr[0], size_needed);
		if (result == 0)
		{
			throw std::runtime_error("Failed to convert string to wstring.");
		}

		return wstr;
	}
};

