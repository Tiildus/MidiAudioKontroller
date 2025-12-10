#include "ButtonHandler.h"
#include "WindowUtils.h"
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

void ButtonHandler::toggleMediaPlayPause() {
    std::system("playerctl play-pause &");
    std::cout << "[ButtonHandler] Toggled Play/Pause via playerctl\n";
}

void ButtonHandler::sendKeySequence(const std::vector<std::string>& args) {
    // Join all arguments into a single shell command
    std::string cmd = "ydotool ";
    for (const auto& arg : args) {
        // If argument contains a space, quote it
        if (arg.find(' ') != std::string::npos)
            cmd += "\"" + arg + "\" ";
        else
            cmd += arg + " ";
    }

    // Trim trailing space
    if (!cmd.empty()) cmd.pop_back();

    // Execute command
    int result = std::system(cmd.c_str());

    std::cout << "[ButtonHandler] Executed: " << cmd
    << " (exit code " << result << ")\n";
}

void ButtonHandler::forceCloseFocusedWindow() {
    int pid = getFocusedWindowPID();
    if (pid > 0) {
        std::system(("kill -15 " + std::to_string(pid)).c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::system(("kill -9 " + std::to_string(pid)).c_str());
        std::cout << "[ButtonHandler] Forced closed PID: " << pid << "\n";
    } else {
        std::cout << "[ButtonHandler] No focused PID found, unable to close\n";
    }
}
