#pragma once
#include <QString>

class Overlay {
public:
    Overlay() = default;
    void showVolume(float volume);
    void showText(const QString &title, const QString &text);

private:
    void showKDEOSD(const QString &title, const QString &text);
};