#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <thread>

#include "Sound.hpp"

SoundManager::~SoundManager() {
    for (auto& pair : soundBuffers) {
        alDeleteBuffers(1, &pair.second);
    }
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void SoundManager::Init() {
    device = alcOpenDevice(nullptr);
    if (!device) {
        std::cerr << "Failed to open OpenAL device!\n";
        return;
    }
    context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);
}

bool SoundManager::addSound(const std::string& name, const std::string& filepath) {
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

ALuint SoundManager::findSource(const std::string& name) const {
    auto it = sources.find(name);
    if (it == sources.end()) return;

    ALuint source = it->second;
    return source;
}

ALuint SoundManager::findBuffer(const std::string& name) const {
    auto it = soundBuffers.find(name);
    if (it == soundBuffers.end()) return;

    ALuint buffer = it->second;
    return buffer;
}

void SoundManager::play(const std::string& name) {
    ALuint buffer = findBuffer(name);

    ALuint source;
    if (sources.find(name) == sources.end()) {
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
        sources[name] = source;
    } else {
        source = sources[name];
    }

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

void SoundManager::stop(const std::string& name) const {
    ALuint source = findSource(name);
    alSourceStop(source);
}

void SoundManager::pause(const std::string& name) const {
    ALuint source = findSource(name);
    alSourcePause(source);
}

void SoundManager::resume(const std::string& name) const {
    ALuint source = findSource(name);
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);

    if (state == AL_PAUSED) {
        alSourcePlay(source);
    }
}

void SoundManager::setLooping(const std::string& name, bool loop) const {
    ALuint source = findSource(name);
    alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
}

void SoundManager::setVolume(const std::string& name, float volume) const {
    ALuint source = findSource(name);
    volume = std::min(1.0f, std::max(0.0f, volume));
    alSourcef(source, AL_GAIN, volume);
}

void SoundManager::setPosition(const std::string& name, float x, float y, float z=0.0f) {
    ALuint source = findSource(name);
    alSource3f(source, AL_POSITION, x, y, z);
}

void SoundManager::setListenerPosition(float x, float y, float z) {
    float defaultOrientation[] = {
        0.0f, 0.0f, -1.0f,
        0.0f, 1.0f,  0.0f,
    };
    setListenerPosition(x, y, z, defaultOrientation);
}

void SoundManager::setListenerPosition(float x, float y, float z, const float orientation[6]) {
    alListener3f(AL_POSITION, x, y, z);
    alListenerfv(AL_ORIENTATION, orientation);
}
