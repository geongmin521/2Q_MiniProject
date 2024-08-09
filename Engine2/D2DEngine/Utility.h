#pragma once
class Utility
{
public:
	static int RandomBetween(int min, int max) //���ø����� �������? 
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(min, max);
		return dis(gen);
	}

	template<typename T>
	static void removeElements(std::list<T*>& origin, const std::list<T*>& remove) { //���ﰴü�� ������ ����� �̰� ��ƿ�� ���ø����� �����?
		for (auto it = remove.begin(); it != remove.end(); ++it) {
			origin.remove(*it);
		}
	}
};

