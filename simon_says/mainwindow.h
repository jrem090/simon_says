#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool game_started;
    bool in_playback;
    int  hi_score;
    int  current_score;
    int  index;
    QTimer timer;
    std::vector<int> sequence;

    void HandlePress(int button_pressed);
    void ShowCurrentSequence();
    void setAllUp();


public slots:
    void GreenPress();
    void RedPress();
    void YellowPress();
    void BluePress();
    void showNext();
    void slotUp();
};

#endif // MAINWINDOW_H
