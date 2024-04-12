#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPixmap>
#include <QColor>
#include <QList>
#include <QDebug>
#include <QtMath>

MainWindow::MainWindow(QWidget *_parent) :
    QMainWindow(_parent),
    m_ui(new Ui::MainWindow)
{
    prepareUi();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::encryptSlot()
{
    QList<QList<QList<int>>> H;

    for (int a = 0; a < m_bigImage.width(); ++a)
    {
        QList<QList<int>> b_matrix;
        for (int b = 0; b < m_bigImage.height(); ++b)
        {
            QList<int> R_line;
            for (int R = 0; R < m_bigImage.width(); ++R)
            {
                R_line.append(0);
            }

            b_matrix.append(R_line);
        }

        H.append(b_matrix);
    }


    for (int x = 0; x < m_bigImage.width(); ++x)
    {
        for (int y = 0; y < m_bigImage.height(); ++y)
        {
            QColor pixel = m_bigImage.pixelColor(x, y);
            if (pixel.red() > 128)
            {
                continue;
            }


            for (int a = 0; a < m_bigImage.width(); ++a)
            {
                for (int b = 0; b < m_bigImage.height(); ++b)
                {
                    int R = qRound(sqrt(pow(x - a, 2) + pow(y - b, 2)));

                    if (R >= 0 && R < m_bigImage.width())
                    {
                        H[a][b][R] += 1;
                    }
                }
            }
        }
    }

    int maxA = 0;
    int maxB = 0;
    int maxR = 0;
    for (int a = 0; a < m_bigImage.width(); ++a)
    {
        for (int b = 0; b < m_bigImage.height(); ++b)
        {
            for (int R = 0; R < m_bigImage.width(); ++R)
            {
                if (H[maxA][maxB][maxR] < H[a][b][R])
                {
                    maxA = a;
                    maxB = b;
                    maxR = R;
                }
            }
        }
    }

    QColor color(255, 0, 0);
    for (int x = maxA - maxR; x < maxA + maxR; ++x)
    {
        for (int y = maxB - maxR; y < maxB + maxR; ++y)
        {
            if (x < 0 || x >= m_bigImage.width())
            {
                continue;
            }

            int R = qRound(sqrt(pow(x - maxA, 2) + pow(y - maxB, 2)));

            if (R == maxR)
            {
                m_bigImage.setPixelColor(x, y, color);
            }
        }
    }

    m_ui->encryptImage->setScaledContents(true);
    m_ui->encryptImage->setPixmap(QPixmap::fromImage(m_bigImage));

    m_ui->statusbar->showMessage(QString::fromUtf8("Найдена окружность: (%1, %2, %3)")
                                 .arg(maxA).arg(maxB).arg(maxR));
}

void MainWindow::swapImage1Slot()
{
    m_bigImage = QImage(":/images/first").convertToFormat(QImage::Format_RGB32);
    m_ui->bigImage->setPixmap(QPixmap::fromImage(m_bigImage));

    m_ui->statusbar->showMessage(QString::fromUtf8("Установлена первая картинка"));
}

void MainWindow::swapImage2Slot()
{
    m_bigImage = QImage(":/images/second").convertToFormat(QImage::Format_RGB32);
    m_ui->bigImage->setPixmap(QPixmap::fromImage(m_bigImage));

    m_ui->statusbar->showMessage(QString::fromUtf8("Установлена вторая картинка"));
}

void MainWindow::prepareUi()
{
    m_ui->setupUi(this);
    initConnections();

    m_bigImage = QImage(":/images/first").convertToFormat(QImage::Format_RGB32);
    m_ui->bigImage->setScaledContents(true);
    m_ui->bigImage->setPixmap(QPixmap::fromImage(m_bigImage));
}

void MainWindow::initConnections()
{
    connect(m_ui->pbEncrypt, &QPushButton::clicked,
            this,            &MainWindow::encryptSlot);

    connect(m_ui->pbImage1,   &QPushButton::clicked,
            this,            &MainWindow::swapImage1Slot);
    connect(m_ui->pbImage2,   &QPushButton::clicked,
            this,            &MainWindow::swapImage2Slot);
}

