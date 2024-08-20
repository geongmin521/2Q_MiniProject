#include "pch.h"
#include "Music.h"

namespace Music
{
    SoundManager* SoundManager::mInstance = nullptr;
    SoundManager* soundManager = SoundManager::GetInstance();  // �ʱ�ȭ  

    SoundManager* SoundManager::GetInstance() 
    {
        if (mInstance == nullptr)
            mInstance = new SoundManager();  

        return mInstance;
    }

    void SoundManager::DestroyInstance()
    {
        delete mInstance;
        mInstance = nullptr;
    }

    void SoundManager::Init()
    {
        System_Create(&mSystem);
        mSystem->init(20, FMOD_INIT_NORMAL, 0);
    }

    void SoundManager::LoadMusic(eSoundList soundlist, bool loopcheck, const std::string& path)
    {
        if (loopcheck)
            mSystem->createSound(path.c_str(), FMOD_LOOP_NORMAL, 0, &mSoundList[static_cast<int>(soundlist)]);
        else
            mSystem->createSound(path.c_str(), FMOD_LOOP_OFF, 0, &mSoundList[static_cast<int>(soundlist)]);
    }

    void SoundManager::PlayMusic(eSoundList soundlist, eSoundChannel channel)
    {
        mChannel[static_cast<int>(channel)]->stop();
        mSystem->playSound(mSoundList[static_cast<int>(soundlist)], nullptr, 0, &mChannel[static_cast<int>(channel)]);
    }

    void SoundManager::StopMusic(eSoundChannel channel)
    {
        mChannel[static_cast<int>(channel)]->stop();
    }

    void SoundManager::SetVolume(float volume, eSoundChannel chanel)
    {
        mChannel[(int)chanel]->setVolume(volume);
    }

    SoundManager::SoundManager(): mSystem(), mChannel{}, mSoundList{}, mVolume(0.3f)
    {
    }

    SoundManager::~SoundManager()
    {
        mSystem->release();
        mSystem->close();
    }
};