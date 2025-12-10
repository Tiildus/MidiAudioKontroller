#pragma once
#include <RtMidi.h>
#include <functional>

class MidiHandler {
public:
    using CCCallback = std::function<void(int cc, float value)>;
    using ButtonCallback = std::function<void(int note)>;

    MidiHandler(const std::string& deviceName);
    ~MidiHandler();
    
    void setCallback(CCCallback cb);
    void setButtonCallback(ButtonCallback cb);
    void startListening();

private:
    RtMidiIn midiIn;
    CCCallback callback;
    ButtonCallback buttonCallback;
    static void staticMidiCallback(double dt, std::vector<unsigned char>* message, void* userData);
};
