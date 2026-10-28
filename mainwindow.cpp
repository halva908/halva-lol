#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_stopwatch(new Stopwatch(this))
{
    setupUI();

    connect(m_startStopButton, &QPushButton::clicked,
            this, &MainWindow::onStartStopClicked);
    connect(m_clearButton, &QPushButton::clicked,
            this, &MainWindow::onClearClicked);
    connect(m_lapButton, &QPushButton::clicked,
            this, &MainWindow::onLapClicked);

    connect(m_stopwatch, &Stopwatch::timeUpdated,
            this, &MainWindow::onTimeUpdated);
    connect(m_stopwatch, &Stopwatch::lapRecorded,
            this, &MainWindow::onLapRecorded);

    m_lapButton->setEnabled(false);
}

void MainWindow::setupUI()
{
    setWindowTitle(QStringLiteral("Секундомер"));
    resize(400, 350);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    m_timeLabel = new QLabel(QStringLiteral("0.0 сек"), this);
    m_timeLabel->setAlignment(Qt::AlignCenter);
    QFont font = m_timeLabel->font();
    font.setPointSize(24);
    m_timeLabel->setFont(font);
    mainLayout->addWidget(m_timeLabel);

    m_lapBrowser = new QTextBrowser(this);
    mainLayout->addWidget(m_lapBrowser);

    QHBoxLayout *btnLayout = new QHBoxLayout();

    m_startStopButton = new QPushButton(QStringLiteral("Старт"), this);
    m_clearButton     = new QPushButton(QStringLiteral("Очистить"), this);
    m_lapButton       = new QPushButton(QStringLiteral("Круг"), this);

    btnLayout->addWidget(m_startStopButton);
    btnLayout->addWidget(m_clearButton);
    btnLayout->addWidget(m_lapButton);

    mainLayout->addLayout(btnLayout);
}

void MainWindow::onStartStopClicked()
{
    if (m_stopwatch->isRunning()) {
        m_stopwatch->stop();
        m_startStopButton->setText(QStringLiteral("Старт"));
        m_lapButton->setEnabled(false);
    } else {
        m_stopwatch->start();
        m_startStopButton->setText(QStringLiteral("Стоп"));
        m_lapButton->setEnabled(true);
    }
}

void MainWindow::onClearClicked()
{
    m_stopwatch->reset();
    m_startStopButton->setText(QStringLiteral("Старт"));
    m_lapButton->setEnabled(false);
    m_lapBrowser->clear();
    m_timeLabel->setText(QStringLiteral("0.0 сек"));
}

void MainWindow::onLapClicked()
{
    m_stopwatch->lap();
}

void MainWindow::onTimeUpdated(double totalSeconds)
{
    m_timeLabel->setText(
        QString::number(totalSeconds, 'f', 1) + QStringLiteral(" сек"));
}

void MainWindow::onLapRecorded(int lapNumber, double lapTime)
{
    m_lapBrowser->append(
        QString(QStringLiteral("Круг %1, время: %2 сек"))
            .arg(lapNumber)
            .arg(lapTime, 0, 'f', 1));
}
