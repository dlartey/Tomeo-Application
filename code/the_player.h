//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include <vector>
#include <QTimer>

class ThePlayer : public QMediaPlayer {

Q_OBJECT

private:
    std::vector<TheButtonInfo>* infos;
    std::vector<TheButton*>* buttons;
    QTimer* mTimer;
    long updateCount = 0;
    bool isplaying;
    bool muted;
    int vol;

public:
    ThePlayer() : QMediaPlayer(NULL) {
        setVolume(0); // be slightly less annoying
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );

        mTimer = new QTimer(NULL);
        mTimer->setInterval(1000); // 1000ms is one second between ...
        mTimer->start();
        isplaying = true;
        vol = 50;
    }

    // all buttons have been setup, store pointers here
    void setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i);

    void setisplaying(bool val) {
        isplaying = val;
    }

    bool getisplaying() {
        return isplaying;
    }

    void setmuted(bool val) {
        muted = val;
    }

    bool getmuted() {
        return muted;
    }

    void setvol(int val) {
        vol = val;
    }

    int getvol() {
        return vol;
    }

private slots:

    void playStateChanged (QMediaPlayer::State ms);

public slots:

    // start playing this ButtonInfo
    void jumpTo (TheButtonInfo* button);
    void pausing ();
    void playing ();
    void mute();

};

#endif //CW2_THE_PLAYER_H
