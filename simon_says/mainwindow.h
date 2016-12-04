#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 * This class is responsible for the logic behind the the simon says game.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //METHODS

    /**
     * Method for responding to a button press
     * @param button_pressed Index of the button pressed
     */
    void HandlePress(int button_pressed);

    /**
     * Add next item in sequence and playback
     */
    void ShowCurrentSequence();

    /**
     * set all buttons in an up position
     */
    void setAllUp();

    //DATA

    Ui::MainWindow *ui;

    bool game_started;
    bool in_playback;

    unsigned int hi_score;
    unsigned int index;

    std::vector<int> sequence;


public slots:
    void GreenPress();
    void RedPress();
    void YellowPress();
    void BluePress();
    void showNext();
    void slotUp();
};

#endif // MAINWINDOW_H
