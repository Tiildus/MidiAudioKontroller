#pragma once
#include <vector>
#include <string>

class ButtonHandler {
public:
    ButtonHandler() = default;
    void toggleMediaPlayPause();
    void sendKeySequence(const std::vector<std::string>& keys);
    void forceCloseFocusedWindow();
};
