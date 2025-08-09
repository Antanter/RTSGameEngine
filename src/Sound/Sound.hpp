#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

#include <unordered_map>
#include <string>

class SoundManager {
    private:
    std::unordered_map<std::string, ALuint> soundBuffers;
    std::unordered_map<std::string, ALuint> sources;

    ALCdevice* device = nullptr;
    ALCcontext* context = nullptr;

    bool addSound(const std::string& name, const std::string& filepath);
    ALuint findSource(const std::string& name) const;
    ALuint findBuffer(const std::string& name) const; 

    public:
    SoundManager();
    ~SoundManager();

    void Init();
    void play(const std::string& name);

    void stop(const std::string& name) const;
    void pause(const std::string& name) const;
    void resume(const std::string& name) const;

    void setLooping(const std::string& name, bool loop) const;
    void setVolume(const std::string& name, float volume) const;

    void setPosition(const std::string& name, float x, float y, float z);
    void setListenerPosition(float x, float y, float z);
    void setListenerPosition(float x, float y, float z, const float position[]);

    void playMusic(const std::string& filepath, bool loop = true);
    void stopMusic();
    void fadeOutMusic(float seconds);

    void stopAll();
};
