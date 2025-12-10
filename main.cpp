#include "MidiHandler.h"
#include "AudioHandler.h"
#include "Overlay.h"
#include "WindowUtils.h"
#include "ButtonHandler.h"

int main(int argc, char *argv[]) {
    Overlay overlay;
    AudioHandler audio;
    ButtonHandler button;
    MidiHandler midi("Midi Through Port-0");

    // --- Volume Controls ---
    midi.setCallback([&](int cc, float vol) {
        switch (cc) {
            case 0: audio.setVolumeForApp("spotify", vol); break;
            case 1: audio.setVolumeForApp("firefox", vol); break;
            case 2: audio.setVolumeForApp("discord", vol); break;
            case 3: audio.setVolumeForPID(getFocusedWindowPID(), vol); break;
        }
        overlay.showVolume(vol);
    });

    // --- Button Controls ---
    midi.setButtonCallback([&](int note) {
        switch (note) {
            case 0: button.toggleMediaPlayPause(); break;
            case 1: button.sendKeySequence({"type", "Hello World"}); break; //must be formated for wtype
            case 2: button.forceCloseFocusedWindow(); break;
            case 3: break; // reserved
        }
    });

    midi.startListening();
}
