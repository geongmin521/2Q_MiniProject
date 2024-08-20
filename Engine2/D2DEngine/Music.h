#pragma once
// FMOD
#ifndef _WIN64
#include "fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
using namespace FMOD;
#endif
#ifdef _WIN64
#include "fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
using namespace FMOD;
#endif
#include <string>

namespace Music
{
    enum class eSoundChannel
    {
        BGM,
        Effect,
        Effect2,
        Size
    };

    enum class eSoundList
    {
        GameOver,
        MainTheme,
        BatDestroy,
        Lock,
        Reward,
        WaveStart,
        TowerUpgrade,
        PileHitted,
        Size
    };
    class SoundManager;  
    extern SoundManager* soundManager;  
    class SoundManager final
    {
    public:
        static SoundManager* GetInstance();

        static void DestroyInstance();

        void Init();

        void LoadMusic(eSoundList soundlist, bool loopcheck, const std::string& path);

        void PlayMusic(eSoundList list, eSoundChannel channel);

        void StopMusic(eSoundChannel channel);

        void SetVolume(float volume, eSoundChannel chanel);

        void SetIsWrong(int index, bool ture) { IsWrong[index] = ture;}


    private:
        SoundManager();

        ~SoundManager();

    private:
        static SoundManager* mInstance;
        bool IsWrong[6] = { false, false, false, false, false, false };
        FMOD::System* mSystem;
        FMOD::Channel* mChannel[static_cast<int>(eSoundChannel::Size)];
        FMOD::Sound* mSoundList[static_cast<int>(eSoundList::Size)];
        float mVolume;
    };

}