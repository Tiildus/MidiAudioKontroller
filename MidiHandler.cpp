#include "MidiHandler.h"
#include <iostream>
#include <thread>
#include <chrono>

MidiHandler::MidiHandler(const std::string& deviceName) {
    //seaches through available midi devices and opens the one that matches deviceName
    unsigned int ports = midiIn.getPortCount();
    for (unsigned int i = 0; i < ports; ++i) {
        //opens midi device that matchs deviceName and sets the callback function
        if (midiIn.getPortName(i).find(deviceName) != std::string::npos) {
            midiIn.openPort(i);
            midiIn.setCallback(&MidiHandler::staticMidiCallback, this);
            midiIn.ignoreTypes(false, false, false);
            std::cout << "[Midi] Connected to Midi Device\n";
            break;
        }
    }
}

MidiHandler::~MidiHandler() {
    midiIn.cancelCallback();
    midiIn.closePort();
}

//sets the callback function from the main application
//the function should take two parameters: int cc, float volume
void MidiHandler::setCallback(CCCallback cb) {
    callback = cb;
}

//sets the button callback function from the main application
void MidiHandler::setButtonCallback(ButtonCallback cb) {
    buttonCallback = cb;
}

//keeps the application running to listen for MIDI messages
void MidiHandler::startListening() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

//static callback function that processes incoming MIDI messages
//uses callback that was set by the main application
void MidiHandler::staticMidiCallback(double, std::vector<unsigned char>* message, void* userData) {
    auto* self = static_cast<MidiHandler*>(userData);
    if (message->size() >= 3) {
        unsigned char status = (*message)[0];
        unsigned char data1 = (*message)[1];
        unsigned char data2 = (*message)[2];

        unsigned char messageType = status & 0xF0;

        if (messageType == 0xB0) {
            float volume = data2 / 127.0f;
            if (self->callback) {
                self->callback(data1, volume);
            } 
        }
        else if (messageType == 0x90 && data2 > 0) {
            if (self->buttonCallback) {
                self->buttonCallback(data1);
            }
        }
    }
}
