#include "WindowUtils.h"
#include <cstdlib>
//#include <iostream>
//#include <QDBusInterface>

int getFocusedWindowPID() {
    FILE* pipe = popen("kdotool getactivewindow getwindowpid", "r");
    if (!pipe) return -1;
    char buffer[128];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    try {
        return std::stoi(result);
    } catch (...) {
        return -1;
    }
}

/*
int getFocusedWindowPID() {
    QDBusInterface iface("org.kde.KWin", "/KWin", "org.kde.KWin");
    QDBusMessage reply = iface.call("activeWindowPid");
    if (reply.type() == QDBusMessage::ReplyMessage && !reply.arguments().isEmpty())
        return reply.arguments().first().toInt();
    return -1;
}
*/
