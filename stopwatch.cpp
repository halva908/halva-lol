#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent)
    : QObject(parent)
    , m_timer(new QTimer(this))
    , m_totalTime(0.0)
    , m_lastLapTime(0.0)
    , m_lapCount(0)
    , m_running(false)
{
    m_timer->setInterval(100);
    connect(m_timer, &QTimer::timeout, this, &Stopwatch::onTimeout);
}

void Stopwatch::start()
{
    if (!m_running) {
        m_running = true;
        m_timer->start();
    }
}

void Stopwatch::stop()
{
    if (m_running) {
        m_running = false;
        m_timer->stop();
    }
}

void Stopwatch::reset()
{
    stop();
    m_totalTime   = 0.0;
    m_lastLapTime = 0.0;
    m_lapCount    = 0;
    emit timeUpdated(m_totalTime);
}

void Stopwatch::lap()
{
    if (!m_running)
        return;

    m_lapCount++;
    double lapTime = m_totalTime - m_lastLapTime;
    m_lastLapTime = m_totalTime;
    emit lapRecorded(m_lapCount, lapTime);
}

bool Stopwatch::isRunning() const
{
    return m_running;
}

void Stopwatch::onTimeout()
{
    m_totalTime += 0.1;
    emit timeUpdated(m_totalTime);
}
