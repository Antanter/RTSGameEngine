#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

class SoundManager {
    private:
    
    std::unordered_map<std::string, ALuint> soundBuffers;
    ALCdevice* device = nullptr;
    ALCcontext* context = nullptr;

    public:

    bool addSound(const std::string& name, const std::string& filepath) {
        if (soundBuffers.count(name)) { return true; }

        SF_INFO sfInfo;
        SNDFILE* sndFile = sf_open(filepath.c_str(), SFM_READ, &sfInfo);
        if (!sndFile) {
            std::cerr << "Failed to open sound file: " << filepath << "\n";
            return false;
        }

        std::vector<short> samples(sfInfo.frames * sfInfo.channels);
        sf_read_short(sndFile, samples.data(), samples.size());
        sf_close(sndFile);

        ALenum format = (sfInfo.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

        ALuint buffer;
        alGenBuffers(1, &buffer);
        alBufferData(buffer, format, samples.data(), samples.size() * sizeof(short), sfInfo.samplerate);

        soundBuffers[name] = buffer;
        std::cout << "Loaded sound: " << name << " -> " << filepath << "\n";
        return true;
    }

    SoundManager() {
        device = alcOpenDevice(nullptr);
        if (!device) {
            std::cerr << "Failed to open OpenAL device!\n";
            return;
        }
        context = alcCreateContext(device, nullptr);
        alcMakeContextCurrent(context);

        addSound("best", "");
    }

    ~SoundManager() {
        for (auto& pair : soundBuffers) {
            alDeleteBuffers(1, &pair.second);
        }
        alcDestroyContext(context);
        alcCloseDevice(device);
    }

    void play(const std::string& name) {
        if (!soundBuffers.count(name)) {
            std::cerr << "Sound not found: " << name << "\n";
            return;
        }

        ALuint buffer = soundBuffers[name];

        ALuint source; 
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
        alSourcePlay(source);

        std::thread([source]() {
            ALint state;
            do {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                alGetSourcei(source, AL_SOURCE_STATE, &state);
            } while (state == AL_PLAYING);

            alDeleteSources(1, &source);
        }).detach();
    }
};
