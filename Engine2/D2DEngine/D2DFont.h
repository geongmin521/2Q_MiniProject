#pragma once

enum Setting // �뵵 ���� ���� �ϱ� ���ؼ�
{
	LEFT,
	MIDDLE,
	RIGHT,
	TOP,
	BOTTOM,
	EXIT
};

class Transform;
class D2DFont // ���� �̸� Font���µ� ����ü�� �̹� �־ ������
{
public:
	D2DFont();
	~D2DFont();

private:
	float FontSize = 10; 
	D2D1_POINT_2F Pos = {0.f , 0.f};
	D2D_SIZE_F BoxSize = { 100.f, 50.f };

	ID2D1SolidColorBrush* FontBrush = nullptr;
	IDWriteTextFormat* DWriteTextFormat = nullptr;;
	IDWriteTextLayout* DWriteTextLayout = nullptr;;

	Transform* transform = nullptr;
	bool IsTransform = false; 
public:
	void Update(float deltaTime);
	void DrawFont(D2D1_COLOR_F color);  // �ۼ��� ������ �׸�

	void SetPos(float _X, float _Y) { Pos = { _X , _Y }; } // ��ġ ���� ������ǥ�϶� ���
	void SetBoxSize(float width, float height) { BoxSize.width = width; BoxSize.height = height;} // �ؽ�Ʈ�ڽ� ������ 

	void LoadFont(std::wstring FontName); // �뵵 ������ �۲ÿ� �ִ� ��Ʈ�� �ε��ϴ� ��

	void CreateLayoutText(std::wstring detail); // �ؽ�Ʈ ������ �ۼ�
	void SetSize(float _FontSize , DWRITE_TEXT_RANGE textRange); // DWRITE_TEXT_RANGE ���� {0 , 9 } �̷��� ������ 0���� 9��° ������ ���� ũ�⸦ ����
	
	// ��Ʈ ���� �߸� �־����� ��� �߾����� ���ĵǰ� ������
	void Sort(Setting _Sort); // ����, ���, ������ ����
	void SetFontLocation(Setting _Sort); // ���� ����, �߰�, �Ʒ��� ����

	void OnTransform(); // Ʈ�������� �̿��� ������ ��� ���
	Transform* GetTransform() { return transform; }
};

/// ��� ���� /// 
// �Ʒ��� 2���� ���� ������ �ϰ� LoadFont(L"�������� �۲�");�� �ϸ� �ȴ�.
// D2D1_POINT_2F Pos = { 0.f , 0.f };
// D2D_SIZE_F BoxSize = { 100.f, 50.f };
// ������ D2DFont test; test.CreateLayoutText(L"�ȳ��ϼ���");
// ��Ʈ ���� �� ������ ������ ������ �Ǳ����� �ϸ� ���� ���� ������ �ȴ�.

// Ʈ�������� ����ϴ� ���� OnTransform() �Լ��� ����ϰ� ���� GetTransform()->SetParent(������Ʈ�� Ʈ�������� �ϸ� �ȴ�.)