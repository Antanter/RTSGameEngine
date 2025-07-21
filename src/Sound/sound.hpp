#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

#include <unordered_map>
#include <string>

class SoundManager {
    private:
    
    std::unordered_map<std::string, ALuint> soundBuffers;
    ALCdevice* device = nullptr;
    ALCcontext* context = nullptr;

    bool addSound(const std::string& name, const std::string& filepath);

    public:

    SoundManager();
    ~SoundManager();

    void play(const std::string& name);
};
