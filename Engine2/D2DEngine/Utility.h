#pragma once
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

	static std::wstring convertFromString(const std::string& str) { //���.. wstring���� string����ȯ�ϴϱ�.. �ѱ��� ������? 
		std::wstring wstr;
		wstr.assign(str.begin(), str.end());
		return wstr;
	}
};

