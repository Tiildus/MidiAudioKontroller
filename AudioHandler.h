#pragma once
#include <pulse/pulseaudio.h>
#include <string>
#include <optional>

class AudioHandler {
public:
    AudioHandler();
    ~AudioHandler();

    void setVolumeForApp(const std::string& appName, float volume);
    void setVolumeForPID(uint32_t pid, float volume);

private:
    pa_mainloop* mainloop;
    pa_context* context;

    // Filter parameters for callback
    std::string targetApp;
    std::optional<uint32_t> targetPID;
    float targetVolume = 1.0f;
    bool applyVolume = false;

    static void contextStateCallback(pa_context* c, void* userdata);
    static void sinkInputInfoCallback(pa_context* c, const pa_sink_input_info* info, int eol, void* userdata);

    void requestSinkInputs();
    void setVolume(uint32_t index, float volume);
};
