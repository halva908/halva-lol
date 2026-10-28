#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTextBrowser>
#include "stopwatch.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onStartStopClicked();
    void onClearClicked();
    void onLapClicked();
    void onTimeUpdated(double totalSeconds);
    void onLapRecorded(int lapNumber, double lapTime);

private:
    void setupUI();

    QPushButton  *m_startStopButton;
    QPushButton  *m_clearButton;
    QPushButton  *m_lapButton;
    QLabel       *m_timeLabel;
    QTextBrowser *m_lapBrowser;
    Stopwatch    *m_stopwatch;
};

#endif // MAINWINDOW_H
