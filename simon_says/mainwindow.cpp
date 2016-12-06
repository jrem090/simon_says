#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <stdio.h>

#include <QTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    in_playback(false),
    is_easy_mode(true),
    hi_score(0),
    index(0)
{
    srand(QDateTime::currentMSecsSinceEpoch());
    ui->setupUi(this);
    connect(ui->RedButton, SIGNAL(clicked(bool)),
            this, SLOT(RedPress()));
    connect(ui->GreenButton, SIGNAL(clicked(bool)),
            this, SLOT(GreenPress()));
    connect(ui->BlueButton, SIGNAL(clicked(bool)),
            this, SLOT(BluePress()));
    connect(ui->YellowButton, SIGNAL(clicked(bool)),
            this, SLOT(YellowPress()));
    connect(ui->mode_button, SIGNAL(pressed()),
            this, SLOT(SwitchModes()));

    game_started = false;
}

//=============================================================================
MainWindow::~MainWindow()
{
    delete ui;
}

//=============================================================================
void MainWindow::GreenPress()
{
    if(!in_playback)
    {
        ui->output_label->setText(QString("green pressed"));
        HandlePress(1);
    }
}

//=============================================================================
void MainWindow::RedPress()
{
    if(!in_playback)
    {
        ui->output_label->setText(QString("red pressed"));
        HandlePress(0);
    }
}

//=============================================================================
void MainWindow::YellowPress()
{
    if(!in_playback)
    {
        ui->output_label->setText(QString("yellow pressed"));
        HandlePress(3);
    }
}

//=============================================================================
void MainWindow::BluePress()
{
    if(!in_playback)
    {
        ui->output_label->setText(QString("blue pressed"));
        HandlePress(2);
    }
}

//=============================================================================
void MainWindow::HandlePress(int button_pressed)
{
    if(game_started)
    {
        //check if next in sequence
        if(button_pressed == sequence.at(index))
        {
            ++index;
            ui->output_label->setText("correct");

            if(index == sequence.size())
            {
                ui->score_label->setText(QString::number(index));
                if(index > hi_score)
                {
                    hi_score = index;
                    ui->hi_score->setText(QString::number(hi_score));
                }
                index = 0;
                ShowCurrentSequence();

            }
        }
        else
        {
            ui->output_label->setText("YOU LOST");
            sequence.clear();
            index = 0;
            ui->score_label->setText(QString::number(index));
            game_started = false;
        }
        //if correct
        //if last in sequence
        //ShowCurrentSequence();
        //else wait for next

    }
    else
    {
        game_started = true;
        ShowCurrentSequence();
    }
}

//=============================================================================
void MainWindow::ShowCurrentSequence()
{
    in_playback = true;
    // if expert mode create new sequence
    if(!is_easy_mode)
    {
        for(int i = 0; i < sequence.size(); ++i)
        {
            sequence.at(i) = rand() % 4;
        }
    }

    //assign last button in sequence
    int i = rand() % 4;
    sequence.push_back(i);

    //start playback of colors in sequence
    QTimer::singleShot(400, this, SLOT(showNext()));

}

//=============================================================================
void MainWindow::setAllUp()
{
    ui->RedButton->setDown(false);
    ui->GreenButton->setDown(false);
    ui->BlueButton->setDown(false);
    ui->YellowButton->setDown(false);
}

//=============================================================================
void MainWindow::slotUp()
{
    setAllUp();
    if(index == sequence.size())
    {
        index = 0;
        in_playback = false;
    }
    else
    {
        QTimer::singleShot(200, this, SLOT(showNext()));
    }
}

//=============================================================================
void MainWindow::showNext()
{
    if(index<sequence.size())
    {
        switch(sequence.at(index))
        {
        case 0:
        {
            ui->RedButton->setDown(true);
            break;
        }
        case 1:
        {
            ui->GreenButton->setDown(true);
            break;
        }
        case 2:
        {
            ui->BlueButton->setDown(true);
            break;
        }
        case 3:
        {
            ui->YellowButton->setDown(true);
            break;
        }
        }
        ++index;
        QTimer::singleShot(500, this, SLOT(slotUp()));
    }
    else
    {
        std::cout << "ERROR HERE" << std::endl;
    }
}

//=============================================================================
void MainWindow::SwitchModes()
{
    // switch button text
    if(is_easy_mode)
    {
        ui->mode_button->setText("Easy Mode");
        ui->centralWidget->setStyleSheet("background-color:black;color:red");
    }
    else
    {
        ui->mode_button->setText("Expert Mode");
        ui->centralWidget->setStyleSheet("background-color:white;color:black");

    }

    // switch mode and restart game
    is_easy_mode = !is_easy_mode;
    sequence.clear();
    index = 0;
    ui->score_label->setText(QString::number(index));
    game_started = false;
    ui->output_label->setText("Mode Changed. Game restarted.");
}
