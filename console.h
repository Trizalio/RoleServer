#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QSocketNotifier>
#include <iostream>
#include <stdio.h>

class Console : public QObject
{
    Q_OBJECT

public:
    Console();

    void run();

signals:
    void quit();
    void send();
    void play();

private:
    QSocketNotifier *m_notifier;

private slots:
    void readCommand();
};

inline Console::Console()
{
    m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
}

#endif // CONSOLE_H
