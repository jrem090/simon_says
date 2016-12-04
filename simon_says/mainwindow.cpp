#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>     /* srand, rand */
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    in_playback(false),
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

    game_started = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GreenPress()
{
    if(!in_playback)
    {
        ui->output_label->setText(QString("green pressed"));
        HandlePress(1);
    }
}
void MainWindow::RedPress()
{
    if(!in_playback)
    {
        ui->output_label->setText(QString("red pressed"));
        HandlePress(0);
    }
}
void MainWindow::YellowPress()
{
    if(!in_playback)
    {
        ui->output_label->setText(QString("yellow pressed"));
        HandlePress(3);
    }
}
void MainWindow::BluePress()
{
    if(!in_playback)
    {
        ui->output_label->setText(QString("blue pressed"));
        HandlePress(2);
    }
}

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

void MainWindow::ShowCurrentSequence()
{

    in_playback = true;
    //assign next button in sequence
    int i = rand() % 4;
    sequence.push_back(i);

    //start playback of colors in sequence
    showNext();

}

void MainWindow::setAllUp()
{
    ui->RedButton->setDown(false);
    ui->GreenButton->setDown(false);
    ui->BlueButton->setDown(false);
    ui->YellowButton->setDown(false);
}

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
