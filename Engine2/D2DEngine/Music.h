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
        Size
    };

    enum class eSoundList
    {
        BGM,
        Size
    };
    class SoundManager;  // 클래스 전방 선언
    extern SoundManager* soundManager;  // extern을 사용하여 외부에서 접근 가능하도록 선언

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

        //void ManageMusic(const Vector3 Playerpos);
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