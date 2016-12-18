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

    ///user interface for the mainwindow class. uses  corresponding the ui file
    Ui::MainWindow *ui;

    /// true if in a game session
    bool game_started;

    /// true if currently playing back sequence
    bool in_playback;

    /// true if in easy mode, false if in expert mode
    bool is_easy_mode;

    /// current high schore
    unsigned int hi_score;

    ///index of current press
    unsigned int index;

    ///stored sequence of button presses
    std::vector<int> sequence;


public slots:
    
    /**
     * Handle a green button press
     */
    void GreenPress();

    /**
     * Handle a red button press
     */
    void RedPress();

    /**
     * Handle a yellow button press
     */
    void YellowPress();

    /**
     * Handle a blue button press
     */
    void BluePress();

    /**
     * Switch mode from easy to expert and vice versa
     */
    void SwitchModes();

    /**
     * Show next button in sequence
     */
    void showNext();

    /**
     * Set all buttons up.
     */
    void slotUp();
};

#endif // MAINWINDOW_H
