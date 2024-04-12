#ifndef MAINWINDOW
#define MAINWINDOW

#include <QMainWindow>
#include <QImage>

namespace Ui
{
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* _parent = nullptr);
    ~MainWindow();

private slots:
    void encryptSlot();
    void swapImage1Slot();
    void swapImage2Slot();

private:
    void prepareUi();
    void initConnections();

private:
    Ui::MainWindow *m_ui;

    QImage m_bigImage;
};

#endif // MAINWINDOW
