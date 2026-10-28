#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT

public:
    explicit Stopwatch(QObject *parent = nullptr);

    void start();
    void stop();
    void reset();
    void lap();
    bool isRunning() const;

signals:
    void timeUpdated(double totalSeconds);
    void lapRecorded(int lapNumber, double lapTime);

private slots:
    void onTimeout();

private:
    QTimer *m_timer;
    double  m_totalTime;
    double  m_lastLapTime;
    int     m_lapCount;
    bool    m_running;
};

#endif // STOPWATCH_H
