#include "Overlay.h"
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDebug>

void Overlay::showVolume(float volume) {
    // Format volume as integer percent
    int percent = static_cast<int>(volume * 100.0f);
    showKDEOSD("Volume", QString::number(percent) + "%");
}

void Overlay::showText(const QString &title, const QString &text) {
    showKDEOSD(title, text);
}

void Overlay::showKDEOSD(const QString &title, const QString &text) {
    // Create a DBus message to call the KDE OSD service
    QDBusMessage msg = QDBusMessage::createMethodCall(
        "org.kde.plasmashell",     // Service name
        "/org/kde/osdService",     // Object path
        "org.kde.osdService",      // Interface
        "showText"                 // Method
    );
    msg << "audio-volume-high" << title + ": " + text;

    // Try sending it on the session bus
    auto reply = QDBusConnection::sessionBus().call(msg, QDBus::NoBlock);
    if (reply.type() == QDBusMessage::ErrorMessage) {
        qWarning() << "[Overlay] KDE OSD not available —" << title << ":" << text;
    }
}
