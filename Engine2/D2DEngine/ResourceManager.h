#pragma once
class D2DRenderer;
class AnimationAsset;
class ResourceManager
{
public:
	ResourceManager(); 
	~ResourceManager();
	static ResourceManager* Instance;
	std::map<std::wstring, ID2D1Bitmap*> m_BitmapMap;
	std::map<std::wstring, AnimationAsset*> animationAssetMap;
	bool CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** bitmap);
	void ReleaseD2DBitmap(std::wstring strFilePath);
	HRESULT NewBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	bool CreateAnimationAsset(std::wstring strFilePath, AnimationAsset** asset);
	void ReleaseAnimationAsset(std::wstring strFilePath);
};

